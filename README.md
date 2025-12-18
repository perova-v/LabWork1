# LabWork1
## Author
Перова Варвара, группа 25.Б81-мм

## Contacts
st141846@student.spbu.ru

## Description
LabWork1 - Loading and processing raster images (BMP).
Implemented features: image rotation (90 degrees clockwise and counter-clockwise); \n 
gaussian blur filter (3x3 kernel); \n
memory management using abstract base class `Image`; \n
correct handling of BMP padding and headers.

## Build
#### To build the application:
make
#### To build and run tests:
make test

## Run
./labwork1 <input_file.bmp>

#### Example:
./labwork1 sample.bmp

## Output
The program will generate:
`rotated_cw.bmp` (Rotated CW)
`rotated_ccw.bmp` (Rotated CCW)
`gaussian.bmp` (Gaussian Blur)
