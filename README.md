# LabWork1
## Author
Перова Варвара, группа 25.Б81-мм

## Contacts
st141846@student.spbu.ru

## Description
LabWork1 - Loading and processing raster images (BMP).

Implemented features: 

image rotation (90 degrees clockwise and counter-clockwise); 

gaussian blur filter (3x3 kernel);

memory management using abstract base class `Image`;

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

`<input_file>_cw.bmp` (Rotated CW)

`<input_file>_ccw.bmp` (Rotated CCW)

`<input_file>_gaussian.bmp` (Gaussian Blur)
