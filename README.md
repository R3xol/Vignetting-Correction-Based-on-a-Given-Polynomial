# Vignetting Correction Based on a Given Polynomial

## Theoretical Description

Vignetting correction involves modifying the intensity of pixels based on their distance from the center of the image. To achieve this, the distance of each pixel from the center of the image is calculated using the Pythagorean theorem. The intensity of each pixel is then multiplied by the value of a polynomial function. The user provides the coefficients of the polynomial, which, when multiplied by the pixel's distance from the center, yield the desired intensity correction.

## Implementation

1. **Load the Image**: Read the image and determine its height and width.
2. **Determine the Center**: Calculate the center of the image.
3. **Input the Polynomial**: Prompt the user to input the polynomial coefficients.
4. **Check Image Channels**: Determine the number of channels in the image (e.g., grayscale or RGB).
5. **Iterate Over Pixels**: Use nested `for` loops to iterate over each pixel in the image.
   - Calculate the distance of the pixel from the center using the Pythagorean theorem.
   - Compute the value of the polynomial correction function based on the distance.
   - Multiply the pixel's intensity (or each channel's intensity for RGB images) by the polynomial value.
6. **Update Pixel Values**: Assign the new intensity values to the pixels.
