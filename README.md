# BinCascade

## Setup
1. Recursive clone repo
```shell
git clone --recursive https://github.com/TNBL265/BinCascade.git
cd BinCascade
```
2. Create AWS IoT things and download necessary credentials into `certs` directory:
- Device certificate as `client.crt`
- Private key file as `client.key`
- Amazon Root CA 1 as `root_cert_auth.crt`
3. Edit menuconfig `idf.py menuconfig`:
- `SSD1306 Configuration`
   - `SCL GPIO number`: 5
   - `SDA GPIO number`: 4
   - `RESET GPIO number`: -1
- `BinCascade Configuration`
  - `AWS IoT Endpoint`: your AWS IoT endpoint
  - `EXAMPLE_EAP_ID`: your SUTD email address
  - `EXAMPLE_EAP_USERNAME`: your SUTD student ID
  - `EXAMPLE_EAP_PASSWORD`: your password
4. Build, flash and monitor
```shell
idf.py build
idf.py flash
idf.py monitor
```
5. Subscribe to `esp32/example/topic` in _MQTT test client_ on AWS IoT
## Things
### ESP-32
- `main/main.c`:
  - Connect to WiFi
  - Start OLED display 
  - Start ultrasonic sensor
  - Connect to AWS IoT

### OLED Display SSD1306
- `ssd1306` directory

### Ultrasonic Sensor HC-SR04
- `hc_sr04` directory

### AWS IoT
- Submodule `esp-aws-iot` from https://github.com/espressif/esp-aws-iot
- `certs` directory for credentials
- `main/aws.c`

## Reference:
- [CCIOTLabs](https://github.com/TONYSKYZENG/CCIOTLabs)
