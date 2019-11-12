## Example: Hosting 3 Models

Run the provided bash script "start.sh" (if the script throws errors, try dos2unix)

- It serializes the .h5 models to .pb (requires TensorFlow 2.0)
- Installs the TensorFlow server
- Launches the server hosting the models
	
*Be careful when running the script multiple times and overwriting the previous models*

Once the server is launched, the models can be called to do predictions.

e.g. POST http://localhost:8501/v1/models/Model_M1:predict

*You can check the model's metadata for its input shape*
*e.g. GET http://localhost:8501/v1/models/Model_M1/versions/1/metadata*
