#include <stdio.h>

#include "lib/edge-impulse-sdk/classifier/ei_run_classifier.h"

// Callback function declaration
static int get_signal_data(size_t offset, size_t length, float *out_ptr);

// Raw features copied from test sample (Edge Impulse > Model testing)
static float input_buf[] = {-4.0027, -6.3842, 1.0107, -4.2434, -7.6590, 1.7207, -3.2925, -6.9006, 1.8564, -3.4711, -7.0605, 1.8377, -3.9927, -7.6137, 1.9396, -3.5636, -7.3177, 1.4490, -2.8134, -6.6598, 0.3286, -2.3468, -6.0961, -0.3194, -1.8112, -5.7338, -0.2201, -1.2612, -5.8929, 0.1047, -1.0757, -6.3577, 0.5421, -0.8532, -6.4246, 0.6804, -0.2529, -5.9675, 0.0880, 0.0453, -5.5648, -0.3985, -0.0511, -5.5675, -0.3167, 0.4149, -5.6037, -0.6970, 1.2008, -5.2935, -1.7011, 1.1946, -4.9330, -2.1826, 0.8146, -4.9898, -1.8611, 1.0452, -5.3675, -1.3406, 1.5954, -5.4745, -1.1229, 1.9775, -4.9562, -1.6267, 2.6442, -4.2317, -2.7023, 3.7180, -3.8874, -3.5036, 4.2929, -3.8025, -3.7225, 4.2051, -3.7199, -3.7457, 4.4932, -3.9466, -3.6582, 5.2554, -4.5113, -3.3942, 5.7650, -4.7952, -3.3232, 6.3777, -4.5250, -3.7574, 7.6998, -4.0642, -4.5341, 9.2022, -3.7747, -5.0666, 10.3569, -3.7425, -4.8732, 11.1809, -3.9118, -4.6309, 11.4732, -4.1164, -5.3516, 11.4124, -4.0938, -6.3322, 11.7765, -3.7839, -6.4649, 12.6668, -3.4439, -6.4979, 13.7720, -3.3156, -7.2769, 14.9297, -3.3740, -7.9134, 15.5303, -3.4123, -7.7952, 15.4353, -3.3087, -7.7886, 15.4425, -3.1709, -8.3169, 15.3456, -3.1705, -8.6023, 14.5614, -3.2754, -8.3756, 14.0040, -3.2792, -8.2556, 14.0883, -3.2472, -8.2987, 13.7158, -3.4102, -8.0955, 12.9486, -3.6324, -7.8953, 12.7552, -3.8186, -7.9075, 12.6617, -4.2466, -7.5950, 12.0064, -4.7911, -6.8749, 11.3991, -5.0537, -6.3813, 11.0863, -5.2146, -6.0603, 10.5878, -5.5039, -5.4552, 10.1189, -5.6598, -4.9514, 10.1167, -5.6337, -4.9733, 10.1974, -5.6603, -5.0302, 10.0115, -5.5232, -4.9769, 9.8467, -4.9138, -5.5504, 9.7560, -4.2450, -6.4791, 9.2718, -4.1634, -6.2916, 8.4948, -4.6852, -5.1716, 7.9704, -5.2214, -4.7859, 7.2548, -5.2635, -4.8232, 5.7180, -5.0865, -3.8028, 4.1107, -5.2736, -2.3096, 3.2358, -5.5867, -1.5915, 2.9644, -5.5847, -1.4619, 3.2381, -5.6581, -1.5931, 3.8233, -6.0703, -2.0574, 3.7742, -6.3094, -2.4129, 2.6718, -6.1541, -2.2915, 1.0740, -5.8878, -2.0579, -0.4608, -5.6813, -1.9046, -1.6184, -5.7601, -1.4385, -2.0412, -6.2084, -0.7938, -1.7755, -6.4433, -0.7554, -1.5021, -6.2216, -1.2272, -1.5632, -6.1147, -1.3768, -1.5010, -6.1441, -1.3509, -1.1949, -5.8431, -1.7220, -1.4179, -5.4903, -1.9792, -2.6045, -5.4901, -1.5178, -4.0886, -5.6791, -0.6702, -5.0714, -6.0402, 0.2481, -5.3319, -6.7487, 1.1075, -5.0103, -7.3350, 1.3772, -4.4329, -7.0547, 0.8105, -4.0392, -6.2108, 0.0410, -3.9652, -5.8199, -0.2878, -3.9731, -5.8891, -0.2414, -3.9658, -5.7877, -0.1442, -4.2651, -5.7001, 0.1009, -5.1645, -5.9217, 0.8551, -6.2178, -6.0483, 1.9501, -6.4343, -5.9339, 2.5917, -5.8415, -5.7662, 2.3388, -5.7641, -5.4228, 1.8070, -6.8045, -5.0318, 1.9527, -8.1796, -4.9760, 2.6949, -9.0130, -5.0155, 3.1001, -9.0427, -4.9721, 3.0558, -8.7088, -5.1742, 3.1863, -8.9359, -5.2835, 3.2922, -9.9678, -4.7415, 2.8348, -10.9524, -4.1178, 2.2591, -11.3809, -3.9845, 2.1054, -11.8941, -3.9716, 2.1403, -12.8831, -3.8469, 2.1416, -13.8986, -3.8558, 2.1427, -14.5731, -4.0394, 2.0449, -14.8299, -4.2328, 1.9113, -14.8038, -4.2920, 1.9076, -14.8800, -4.1516, 1.8778, -15.1821, -3.9761, 1.7110, -15.6760, -3.9656, 1.6287, -16.4025, -4.0023, 1.6815, -17.0957, -4.0101, 1.6680, -17.4736, -4.1060, 1.5080, -17.7918, -4.1528, 1.2809, -18.1422, -4.0907, 1.1468, -18.1187, -4.2495, 1.2127, -17.7763, -4.5459, 1.2918, -17.6838, -4.6019, 1.2517, -17.7038, -4.5938, 1.3257, -17.2496, -4.7540, 1.5990, -16.5001, -4.7649, 1.7370, -15.8806, -4.5030, 1.6111, -15.1383, -4.3747, 1.5088, -14.1175, -4.5171, 1.5533, -13.2769, -4.5625, 1.5201, -12.8202, -4.4026, 1.3264, -12.2752, -4.2868, 1.1223, -11.5528, -4.2226, 0.9205, -11.2554, -4.1120, 0.7241, -11.3676, -4.1828, 0.8306, -11.2252, -4.5352, 1.3327, -10.7536, -4.7356, 1.6662, -10.1033, -4.4792, 1.3248, -9.2201, -4.1578, 0.6314, -8.4024, -4.1975, 0.2448, -7.9627, -4.4838, 0.3304, -7.6457, -4.7875, 0.5786, -7.1548, -5.0734, 0.7305, -6.7111, -5.2901, 0.8284, -6.6342, -5.3781, 0.9639, -6.6560, -5.3699, 0.9539, -6.4331, -5.2817, 0.6079, -6.1032, -5.0424, 0.1012, -5.7163, -4.7931, -0.2984, -5.1649, -4.8386, -0.4634, -4.6631, -5.0534, -0.3602, -4.1370, -5.0388, -0.3613, -3.1924, -4.8635, -0.9048, -2.2934, -4.8443, -1.5274, -2.1443, -4.9125, -1.6170, -2.1619, -4.8334, -1.6236, -1.6058, -4.7516, -2.0323, -1.0625, -4.9706, -2.3491, -1.0807, -5.3636, -2.2315, -1.0837, -5.6068, -2.0662, -0.6728, -5.6566, -2.0880, -0.2136, -5.4683, -2.2731, 0.2627, -4.9722, -2.7291, 1.0281, -4.4413, -3.3030, 1.6190, -4.1937, -3.5592, 1.5707, -4.1594, -3.4932, 1.6611, -4.1728, -3.5524, 2.5016, -4.3443, -3.9032, 3.1171, -4.7618, -4.1827, 2.8754, -5.1173, -4.0691, 2.8755, -5.1726, -3.7746, 3.9066, -5.1261, -3.6389, 5.1898, -5.1287, -3.6038, 5.9104, -5.0815, -3.5340, 6.1541, -5.0333, -3.5323, 6.2675, -5.0772, -3.6180, 6.3374, -5.1157, -3.6258, 6.3216, -5.1133, -3.6124, 6.3857, -5.0412, -3.9288, 6.6537, -4.6681, -4.5562, 6.8814, -4.1592, -4.9281, 6.9495, -4.1219, -4.7739, 7.1748, -4.4730, -4.4830, 7.7380, -4.5814, -4.4097, 8.5238, -4.3763, -4.5376, 9.5263, -4.0718, -4.8445, 10.5969, -3.6770, -5.3001, 11.1396, -3.3551, -5.5771, 11.0938, -3.3314, -5.5540, 11.2036, -3.5345, -5.6187, 11.5077, -3.8325, -5.8439, 11.3359, -4.2750, -5.8404, 10.8887, -4.8543, -5.6169, 10.9079, -5.3377, -5.5587, 11.4965, -5.5231, -5.8630, 12.2202, -5.4739, -6.3566, 12.7970, -5.4373, -6.6472, 13.1876, -5.5008, -6.6090};

int main() {

    signal_t signal;            // Wrapper for raw input buffer
    ei_impulse_result_t result; // Used to store inference output
    EI_IMPULSE_ERROR res;       // Return code from inference
    
    // Calculate the length of the buffer
    size_t buf_len = sizeof(input_buf) / sizeof(input_buf[0]);

    // Make sure that the length of the buffer matches expected input length
    if (buf_len != EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE) {
        printf("ERROR: The size of the input buffer is not correct.\r\n");
        printf("Expected %d items, but got %d\r\n", 
                EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, 
                (int)buf_len);
        return 1;
    }

    // Assign callback function to fill buffer used for processing/inference
    signal.total_length = EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE;
    signal.get_data = &get_signal_data;

    // Perform DSP pre-processing and inference
    res = run_classifier(&signal, &result, false);

    // Print return code and how long it took to perform inference
    printf("run_classifier returned: %d\r\n", res);
    printf("Timing: DSP %d ms, classification %d ms, anomaly %d ms\r\n", 
            result.timing.dsp, 
            result.timing.classification, 
            result.timing.anomaly);

    // Print prediction results
    printf("Predictions:\r\n");
    for (uint16_t i = 0; i < EI_CLASSIFIER_LABEL_COUNT; i++) {
        printf("  %s: ", ei_classifier_inferencing_categories[i]);
        printf("%.5f\r\n", result.classification[i].value);
    }

    return 0;
}

// Callback: fill a section of the out_ptr buffer when requested
static int get_signal_data(size_t offset, size_t length, float *out_ptr) {
    for (size_t i = 0; i < length; i++) {
        out_ptr[i] = (input_buf + offset)[i];
    }

    return EIDSP_OK;
}