It looks like the LoRa module can just plug into the xiao esp32s3 with pins set properly. The v008 code does that.




1. The LoRa pin difference
Sources: firmware-lora-p2p-v015.ino · lora-p2p-v2-v008.ino
LoRa signal	File 1: v015	File 2: v008
SCK (SPI clock)	GPIO 7	D8 / GPIO 7
MISO	GPIO 8	D9 / GPIO 8
MOSI	GPIO 9	D10 / GPIO 9
NSS (chip select)	GPIO 41	D3 / GPIO 4
RESET	GPIO 42	D2 / GPIO 3
BUSY	GPIO 40	D1 / GPIO 2
DIO1 (interrupt)	GPIO 39	D0 / GPIO 1
The pin definitions are in the first file's source and the second file's source.
The crucial difference is that the SPI wires stay on the same GPIO 7, 8 and 9, but the four control signals change.
- v015: Uses GPIO 41, 42, 40 and 39, associated with the internal B2B connection.
- v008: Uses D3, D2, D1 and D0 for NSS, RESET, BUSY and DIO1 respectively, requiring the LoRa module to be wired to those external pins.
