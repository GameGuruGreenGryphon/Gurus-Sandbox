# QR

Generates a QR code and sends it to standard output.

Currently unfinished.

## For Those Uninitiated

QR codes have three different parameters...

### Mode
Determines the set of characters that can be used within the QR code

There are four modes...

- Numeric only	0-9

- Alphanumeric	0-9, A-Z, space, $%*+-./:

- Binary		ISO/IEC 8859-1

- Kanji/kana	Shift JIS X 0208

### Version
Dimensions of the QR code

Ranges from 1 to 40

4 × version number + 17 dots on each side)

- Version 4 is 33x33

- Version 10 is 57x57

- Version 25 is 117x117

- Version 40 is 177x177

### Error correction level
Reed-Solomon error correction over the finite field

- Low - 7% of data bytes can be restored

- Medium - 15% of data bytes can be restored

- Quartile - 25% of data bytes can be restored

- High - 30% of data bytes can be restored
