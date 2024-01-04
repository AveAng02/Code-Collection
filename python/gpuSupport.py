import tensorflow as tf

# Check if GPU is available
if tf.config.list_physical_devices('GPU'):
    print("GPU is available.")
    # Additional GPU-related information
    gpu_devices = tf.config.experimental.list_physical_devices('GPU')
    for gpu_device in gpu_devices:
        print("Name:", gpu_device.name)
        print("Type:", gpu_device.device_type)
else:
    print("No GPU available. TensorFlow will use CPU.")
