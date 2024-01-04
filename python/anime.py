import tensorflow as tf
from tensorflow.keras import layers, models
from tensorflow.keras.preprocessing.image import ImageDataGenerator

# Generator Model
def build_generator(latent_dim):
    model = models.Sequential()

    model.add(layers.Dense(256, input_dim=latent_dim))
    model.add(layers.LeakyReLU(alpha=0.2))
    model.add(layers.Reshape((16, 16, 1)))

    model.add(layers.Conv2DTranspose(128, (4, 4), strides=(2, 2), padding='same'))
    model.add(layers.LeakyReLU(alpha=0.2))

    model.add(layers.Conv2DTranspose(128, (4, 4), strides=(2, 2), padding='same'))
    model.add(layers.LeakyReLU(alpha=0.2))

    model.add(layers.Conv2DTranspose(256, (4, 4), strides=(2, 2), padding='same'))
    model.add(layers.LeakyReLU(alpha=0.2))

    model.add(layers.Conv2D(3, (3, 3), activation='tanh', padding='same'))
    return model

# Discriminator Model
def build_discriminator(input_shape):
    model = models.Sequential()

    model.add(layers.Conv2D(64, (3, 3), strides=(2, 2), padding='same', input_shape=input_shape))
    model.add(layers.LeakyReLU(alpha=0.2))

    model.add(layers.Conv2D(128, (3, 3), strides=(2, 2), padding='same'))
    model.add(layers.LeakyReLU(alpha=0.2))

    model.add(layers.Conv2D(256, (3, 3), strides=(2, 2), padding='same'))
    model.add(layers.LeakyReLU(alpha=0.2))

    model.add(layers.Flatten())
    model.add(layers.Dense(1, activation='sigmoid'))
    return model

# Combine Generator and Discriminator into GAN
def build_gan(generator, discriminator):
    discriminator.trainable = False
    model = models.Sequential()
    model.add(generator)
    model.add(discriminator)
    return model

# Compile Models
latent_dim = 100
generator = build_generator(latent_dim)
discriminator = build_discriminator((64, 64, 3))

discriminator.compile(loss='binary_crossentropy', optimizer=tf.keras.optimizers.Adam(learning_rate=0.0002, beta_1=0.5), metrics=['accuracy'])

gan = build_gan(generator, discriminator)
gan.compile(loss='binary_crossentropy', optimizer=tf.keras.optimizers.Adam(learning_rate=0.0002, beta_1=0.5))

# Load and Preprocess Data
# Ensure you have a dataset of anime characters and adjust the path accordingly.
data_generator = ImageDataGenerator(rescale=1./255)
data_flow = data_generator.flow_from_directory('path/to/anime_dataset', target_size=(64, 64), batch_size=64, class_mode=None)

# Training
epochs = 10000
batch_size = 64

for epoch in range(epochs):
    for batch in range(data_flow.n // batch_size):
        noise = tf.random.normal(shape=(batch_size, latent_dim))
        generated_images = generator.predict(noise)

        real_images = data_flow.next()

        labels_real = tf.ones((batch_size, 1)) * 0.9
        labels_fake = tf.zeros((batch_size, 1))

        d_loss_real = discriminator.train_on_batch(real_images, labels_real)
        d_loss_fake = discriminator.train_on_batch(generated_images, labels_fake)

        d_loss = 0.5 * tf.math.add(d_loss_real, d_loss_fake)

        noise = tf.random.normal(shape=(batch_size, latent_dim))
        labels_gan = tf.ones((batch_size, 1))

        g_loss = gan.train_on_batch(noise, labels_gan)

    if epoch % 100 == 0:
        print(f"Epoch: {epoch}, D Loss: {d_loss[0]}, G Loss: {g_loss}")

        # Save generated images at some intervals
        if epoch % 500 == 0:
            save_generated_images(epoch, generator)
