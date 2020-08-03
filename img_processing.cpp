#define RED_INTENCITY_COEF 0.2126F
#define GREEN_INTENCITY_COEF 0.7152F
#define BLUE_INTENCITY_COEF 0.0722F

extern "C"{
    void otsuBinarize ( unsigned char* data, unsigned int len );
}

void otsuBinarize ( unsigned char* data, unsigned int len ) {
    // histogram and greyscale
    int histogram[256] = {0};

    for (int i = 0; i < len; i += 4) {
        int brightness =  ( data[i] * RED_INTENCITY_COEF ) + 
                            ( data[i + 1] * GREEN_INTENCITY_COEF ) +
                            ( data[i + 2] * BLUE_INTENCITY_COEF );
        histogram[brightness]++;
        data[i] = brightness;
    }

    // otsu binarization threshold calculation

    unsigned int total = len / 4; // H x W; num of pixels
    int sum = 0;
    for( int i = 0; i < 256; ++i )
        sum += i * histogram[i];

    int sumB = 0;
    int wB = 0;
    int wF = 0;

    float varMax = 0;
    int threshold_1 = 0;
    int threshold_2 = 0;

    for (int i = 0; i < 256; ++i) {
        wB += histogram[i];            // Weight-Background
        if (wB == 0) continue;

        wF = total - wB;                 // Weight-Foreground
        if (wF == 0) break;

        sumB += i * histogram[i];

        int mB = sumB / wB;            // Mean-Background
        int mF = (sum - sumB) / wF;    // Mean-Foreground

        // Calculate Between Class Variance
        float varBetween = 1.0F * wB * wF * (mB - mF) * (mB - mF);

        // Check if new maximum found
        if (varBetween >= varMax) {
            threshold_1 = i;
            if (varBetween > varMax) threshold_2 = i;
            varMax = varBetween;
        }
    }

    // Calculated threshold
    int threshold = ( threshold_1 + threshold_2 ) / 2;

    // binarization based on threshold value 
    for (int i = 0; i < len; i += 4) {
        int det = data[i] > threshold; 
        int val = ( det * 255 ) + ( det * 0 );
        data[i] = data[i + 1] = data[i + 2] = val;
    }
}
