/* Purpose(s): Display Fractals
 * Author: Seth Close
 * Date: 1/10/2024
 * Persons discussed w/:
 * References:
 */
#include "ex3q1.h"

double imaginaryNumberAbsolute(double ReA, double ImA){
    //This is the none squarrooted version
    double absVal = (ReA * ReA) + (ImA * ImA);

    return(absVal);
}

int recursiveFractalSeq(double ReC, double ImC, double ReZ, double ImZ, int depth, int maxIterations) {
    double newRe;
    double newIm;

    //The exit condition
    if (depth >= maxIterations) {
        return(depth);
    }
    else {
        //Squareing Z number
        newRe = ((ReZ * ReZ) - (ImZ * ImZ));
        newIm = ((ReZ * ImZ) + (ReZ * ImZ));

        //Adding C
        newRe = newRe + ReC;
        newIm = newIm + ImC;

        //Collecting Absolute value of new number
        double abdVal = imaginaryNumberAbsolute(newRe, newIm);

        //Checking to see if it has diverged
        if (abdVal > 4) { //4 because I am comparing against 2^2 
            return(depth);
        }
    }
    depth += 1; //Increases depth
    return(recursiveFractalSeq(ReC, ImC, newRe, newIm, depth, maxIterations)); //Calls itself
}


int main(){
    int binType; //Reference for type of fractal
    int maxIterations;
    int depth;

    //Ratio for Mandelbrot 
    int MRatioimH = 2;
    int MRatioreW = 3;

    //Ratio for Julia 
    int JRatioimH = 3;
    int JRatioreW = 4;

    //User input

    //Type
    if (scanf("%d", &binType) != 1) { //Data Validation
        return(-1);
    }
    if (binType != 1){
        if(binType != 0) { //Data Validation
            return(-1);
        }
    }

    //Max Iterations
    if ((scanf("%d", &maxIterations) != 1) || maxIterations <= 0) { //Data Validation
        return(-1);
    }

    if (binType == 0) { //Mandelbrot set
        double centRe;
        double centIm;
        double zoomFactor;

        //Center of display
        if (scanf("%lf %lf", &centRe, &centIm) != 2) { //Data Validation
            return(-1);
        }
        //Zoom factor
        if ((scanf("%lf", &zoomFactor) != 1) || zoomFactor <= 0) { //Data Validation
            return(-1);
        }

        //Before Applying Zoom
        zoomFactor = 1.0 / (zoomFactor);
        int imageW = (imageH / 2) * 3; 

        double changeImSize = (double) MRatioimH * zoomFactor;
        double changeReSize = (double) MRatioreW * zoomFactor;

        //Applying Zoom

        //Finding bounds of the fractal
        double complexReScaleHigh = centRe + (changeReSize / 2);
        double complexReScaleLow = centRe - (changeReSize / 2);
        
        double complexImScaleHigh = centIm + (changeImSize / 2);
        double complexImScaleLow = centIm - (changeImSize / 2);

        //Splitting bounds into correct number of pixels
        double vertIncrease = (2.0 / imageH) * zoomFactor;
        double horiIncrease = (3.0 / imageW) * zoomFactor;

        //Finding starting value
        double srtIm = complexImScaleHigh - (vertIncrease / 2);
        double srtRe = complexReScaleLow + (horiIncrease / 2); 

        //PMM formating
        printf("P3\n");
        printf("%d %d\n", imageW, imageH);
        printf("255\n");

        for (double imVal = srtIm ; imVal > complexImScaleLow ; imVal -= vertIncrease) { //Vertical movement / Imaginary component

            for (double reVal = srtRe; reVal < complexReScaleHigh ; reVal += horiIncrease) { //Horizontal movement
                depth = 0;
                double alpha = 0;
                alpha = recursiveFractalSeq(reVal, imVal, 0.0, 0.0, depth, maxIterations); 

                if (alpha == maxIterations) {
                    printf("255 255 255 ");
                }
                else {

                    alpha = alpha / ((double) maxIterations);
                    printf("0 "); //Never any reds

                    //Applying alpha value
                    int green = alpha * 255;
                    int blue = alpha * 153;

                    printf("%d %d ", green, blue);
                }
            }
            printf("\n");
        }
    }

    else { //Julia set
        double ReC;
        double ImC;
        
        //User input
        if (scanf("%lf %lf", &ReC, &ImC) != 2) { //Data Validation
            printf("FALIRE 4");
            return(-1);
        }

        //Finding correct number of width pixels
        int imageW = (imageH / JRatioimH) * JRatioreW;        

        //PPM formating        
        printf("P3\n");
        printf("%d %d\n", imageW, imageH);
        printf("255\n");
   
        //Splitting bounds into correct number of pixels
        double vertIncrease = (double) JRatioimH / imageH;
        double horiIncrease = (double) JRatioreW / imageW;

        //Starting positions
        double srtIm = 1.5 - (vertIncrease / 2);
        double srtRe = -2.0 + (horiIncrease / 2);
 
        for (double imVal = srtIm ; imVal > -1.5 ; imVal -= vertIncrease) { //Vertical movement / Imaginary component

            for (double reVal = srtRe; reVal < 2 ; reVal += horiIncrease) { //Horizontal movement
                depth = 0;
                double alpha = 0;
                alpha = recursiveFractalSeq(ReC, ImC, reVal, imVal, depth, maxIterations); 

                if (alpha == maxIterations) {
                    printf("255 255 255 ");
                }
                else {

                    alpha = alpha / ((double) maxIterations);
                    printf("0 "); //Never any reds

                    int green = alpha * 255;
                    int blue = alpha * 153;

                    printf("%d %d ", green, blue);
                }
            }
            printf("\n");
        }
    }
    return(0);
}