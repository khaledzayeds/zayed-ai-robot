#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "driver/i2s_std.h"
#include "driver/uart.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
static i2s_chan_handle_t tx,rx;
static int32_t raw[512];
static int16_t pcm[256];
static int16_t recording[80000];
static void play(const int16_t *p,size_t n){
 size_t done=0; ESP_ERROR_CHECK(i2s_channel_write(tx,p,n*2,&done,1000));
}
static size_t capture(int16_t *p,int channel){
 size_t n=0; ESP_ERROR_CHECK(i2s_channel_read(rx,raw,sizeof(raw),&n,1000));
 size_t frames=n/8;
 for(size_t i=0;i<frames;i++) p[i]=(int16_t)(raw[2*i+channel]>>16);
 return frames;
}
void app_main(void){
 i2s_chan_config_t a=I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_0,I2S_ROLE_MASTER);
 ESP_ERROR_CHECK(i2s_new_channel(&a,&tx,NULL));
 i2s_std_config_t t={
 .clk_cfg=I2S_STD_CLK_DEFAULT_CONFIG(16000),
 .slot_cfg=I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_16BIT,I2S_SLOT_MODE_MONO),
 .gpio_cfg={.mclk=I2S_GPIO_UNUSED,.bclk=15,.ws=16,.dout=17,.din=I2S_GPIO_UNUSED}};
 t.slot_cfg.slot_mask=I2S_STD_SLOT_BOTH;
 ESP_ERROR_CHECK(i2s_channel_init_std_mode(tx,&t));
 ESP_ERROR_CHECK(i2s_channel_enable(tx));
 i2s_chan_config_t b=I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_1,I2S_ROLE_MASTER);
 ESP_ERROR_CHECK(i2s_new_channel(&b,NULL,&rx));
 i2s_std_config_t r={
 .clk_cfg=I2S_STD_CLK_DEFAULT_CONFIG(16000),
 .slot_cfg=I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_32BIT,I2S_SLOT_MODE_STEREO),
 .gpio_cfg={.mclk=I2S_GPIO_UNUSED,.bclk=4,.ws=5,.dout=I2S_GPIO_UNUSED,.din=6}};
 ESP_ERROR_CHECK(i2s_channel_init_std_mode(rx,&r));
 ESP_ERROR_CHECK(i2s_channel_enable(rx));
 ESP_ERROR_CHECK(uart_driver_install(UART_NUM_0,1024,0,0,NULL,0));
 int channel=0;
 while(1){
 printf("\n1: tone  2: mic levels L/R  3: record/play  4: toggle mic channel (now %d)\n",channel); fflush(stdout);
 uint8_t c;
 do { if(uart_read_bytes(UART_NUM_0,&c,1,pdMS_TO_TICKS(1000))!=1)c=0; }while(c<'1'||c>'4');
 if(c=='1'){
 for(int k=0;k<125;k++){for(int i=0;i<256;i++)pcm[i]=(int16_t)(2000*sin(6.2831853*440*(k*256+i)/16000.0));play(pcm,256);} 
 for(int i=0;i<256;i++){pcm[i]=0;}
 play(pcm,256);printf("Tone done\n");
 }else if(c=='2'){
 for(int k=0;k<50;k++){int peak[2]={0,0};for(int j=0;j<6;j++){size_t n=0;ESP_ERROR_CHECK(i2s_channel_read(rx,raw,sizeof(raw),&n,1000));for(size_t i=0;i<n/8;i++)for(int ch=0;ch<2;ch++){int v=abs(raw[2*i+ch]>>16);if(v>peak[ch])peak[ch]=v;}}printf("MIC L=%d R=%d\n",peak[0],peak[1]);}
 }else if(c=='3'){
 printf("Speak now (5 seconds)\n");fflush(stdout);
 size_t pos=0;while(pos<80000){size_t n=capture(pcm,channel);if(n>80000-pos)n=80000-pos;for(size_t i=0;i<n;i++)recording[pos+i]=pcm[i];pos+=n;}
 printf("Playback\n");for(pos=0;pos<80000;pos+=256){size_t n=80000-pos;if(n>256)n=256;for(size_t i=0;i<n;i++)pcm[i]=recording[pos+i]/2;play(pcm,n);}for(int i=0;i<256;i++){pcm[i]=0;}
 play(pcm,256);
 }else channel=1-channel;
 }
}
