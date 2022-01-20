# Example Standalone Inference

Runs a simple local inference example on Linux, macOS, or Windows. Follow [this guide](https://docs.edgeimpulse.com/v2.0/docs/deploy-your-model-as-a-c-library) to get started.

Basic steps:
 * Download and unzip your Edge Impulse C++ library into the *lib/* directory
 * Copy a test sample's *raw features* into the `input_buf[]` array
 * Enter `make` in this directory to compile the project
 * Enter `./build/my-motion` to run the application
 * Compare the output predictions to the predictions of the test sample in the Edge Impulse Studio

 ## License

 [Appache License v2.0](https://www.apache.org/licenses/LICENSE-2.0)