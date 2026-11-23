#include "wifi_board.h"
#include "codecs/no_audio_codec.h"
#include "display/lcd_display.h"
#include "application.h"
#include "button.h"
#include "config.h"

#include <driver/spi_master.h>
#include <esp_lcd_gc9a01.h>
#include <esp_lcd_panel_io.h>
#include <esp_lcd_panel_ops.h>
#include <esp_lcd_panel_vendor.h>
#include <esp_log.h>

class ZayedAiS3Board : public WifiBoard {
 private:
    Button boot_button_;
    Display* display_ = nullptr;

    void InitializeDisplay() {
        spi_bus_config_t bus = GC9A01_PANEL_BUS_SPI_CONFIG(
            DISPLAY_SPI_SCK_PIN, DISPLAY_SPI_MOSI_PIN,
            DISPLAY_WIDTH * DISPLAY_HEIGHT * sizeof(uint16_t));
        ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &bus, SPI_DMA_CH_AUTO));

        esp_lcd_panel_io_handle_t io = nullptr;
        esp_lcd_panel_handle_t panel = nullptr;
        esp_lcd_panel_io_spi_config_t io_cfg =
            GC9A01_PANEL_IO_SPI_CONFIG(DISPLAY_SPI_CS_PIN, DISPLAY_DC_PIN, nullptr, nullptr);
        io_cfg.pclk_hz = 20 * 1000 * 1000;
        ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi(SPI2_HOST, &io_cfg, &io));

        esp_lcd_panel_dev_config_t panel_cfg = {};
        panel_cfg.reset_gpio_num = DISPLAY_RESET_PIN;
        panel_cfg.rgb_ele_order = LCD_RGB_ELEMENT_ORDER_BGR;
        panel_cfg.bits_per_pixel = 16;
        ESP_ERROR_CHECK(esp_lcd_new_panel_gc9a01(io, &panel_cfg, &panel));
        ESP_ERROR_CHECK(esp_lcd_panel_reset(panel));
        ESP_ERROR_CHECK(esp_lcd_panel_init(panel));
        ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel, true));
        ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel, DISPLAY_SWAP_XY));
        ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel, DISPLAY_MIRROR_X, DISPLAY_MIRROR_Y));
        ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel, true));
        // Backlight GPIO is deliberately not driven until module polarity is verified.
        display_ = new SpiLcdDisplay(io, panel, DISPLAY_WIDTH, DISPLAY_HEIGHT,
                                    DISPLAY_OFFSET_X, DISPLAY_OFFSET_Y,
                                    DISPLAY_MIRROR_X, DISPLAY_MIRROR_Y, DISPLAY_SWAP_XY);
    }

 public:
    ZayedAiS3Board() : boot_button_(BOOT_BUTTON_GPIO) {
        InitializeDisplay();
        boot_button_.OnClick([this]() {
            auto& app = Application::GetInstance();
            if (app.GetDeviceState() == kDeviceStateStarting) {
                EnterWifiConfigMode();
                return;
            }
            app.ToggleChatState();
        });
    }

    AudioCodec* GetAudioCodec() override {
        static NoAudioCodecSimplex codec(
            AUDIO_INPUT_SAMPLE_RATE, AUDIO_OUTPUT_SAMPLE_RATE,
            AUDIO_I2S_SPK_GPIO_BCLK, AUDIO_I2S_SPK_GPIO_LRCK, AUDIO_I2S_SPK_GPIO_DOUT,
            AUDIO_I2S_MIC_GPIO_SCK, AUDIO_I2S_MIC_GPIO_WS, AUDIO_I2S_MIC_GPIO_DIN);
        return &codec;
    }

    Display* GetDisplay() override { return display_; }
};

DECLARE_BOARD(ZayedAiS3Board);
