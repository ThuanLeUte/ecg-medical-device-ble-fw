//////////////////////////////////////////////////////////////////////////////////////////
//
//   Arduino Library for ADS1292R Shield/Breakout
//
//   Copyright (c) 2017 ProtoCentral
//
//   This software is licensed under the MIT License(http://opensource.org/licenses/MIT).
//
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
//   NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//   IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//   SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//   Requires g4p_control graphing library for processing.  Built on V4.1
//   Downloaded from Processing IDE Sketch->Import Library->Add Library->G4P Install
//
/////////////////////////////////////////////////////////////////////////////////////////
#include "bsp_porting.h"

bool bsp_porting_read_pin(uint8_t pin)
{
  // return digitalRead(pin);

  return nrf_gpio_pin_read(pin);
}

void bsp_porting_write_pin(uint8_t pin, bool enable)
{
  bsp_gpio_write(pin, enable);
}

void bsp_porting_delay(uint32_t ms)
{
  bsp_delay_ms(ms);

  // delay(ms);
}

uint8_t bsp_porting_spi_transfer(uint8_t data)
{
  static uint8_t receive_data;

  bsp_spi_transmit_receive(&data, &receive_data, 1);

  return receive_data;

  // return SPI.transfer(data);
}
