## Example: Hosting 3 Models

Requirements:

- Install TensorFlow 2.0
- update the models.config file in a text editor so that the base path of each file is an absolute path

Run the provided bash script "start.sh" (if the script throws errors, try dos2unix)

- It serializes the .h5 models to .pb (requires TensorFlow 2.0)
- Installs the TensorFlow server
- Launches the server hosting the models

*Alternatively* use the individual commands from the script as needed.
	
*Be careful when running the script multiple times and attempting to overwrite previously saved models*

Once the server is launched, the models can be called to do predictions.

e.g. POST http://localhost:8501/v1/models/Model_M1:predict

*You can check the model's metadata for its input shape*
*e.g. GET http://localhost:8501/v1/models/Model_M1/versions/1/metadata*
