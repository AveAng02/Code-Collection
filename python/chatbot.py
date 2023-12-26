import numpy as np
import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Embedding, LSTM, Dense
from tensorflow.keras.preprocessing.text import Tokenizer
from tensorflow.keras.preprocessing.sequence import pad_sequences

# Load and preprocess the Cornell Movie Dialogues Corpus
def load_conversations():
    conversations = []
    with open('movie_lines.txt', encoding='utf-8', errors='ignore') as file:
        lines = file.readlines()
        for line in lines:
            parts = line.split(" +++$+++ ")
            conversation_id = parts[0][1:]
            dialogue = parts[-1].strip()
            conversations.append((conversation_id, dialogue))
    return conversations

def load_lines():
    lines = {}
    with open('movie_lines.txt', encoding='utf-8', errors='ignore') as file:
        for line in file:
            parts = line.split(" +++$+++ ")
            line_id = parts[0]
            text = parts[-1].strip()
            lines[line_id] = text
    return lines

def load_conversation_data(conversation_file, line_file):
    conversations = load_conversations()
    lines = load_lines()

    inputs, outputs = [], []
    for conv_id, dialogue in conversations:
        conversation = conv_id.split()
        for i in range(len(conversation) - 1):
            inputs.append(lines[conversation[i]])
            outputs.append(lines[conversation[i + 1]])

    return inputs, outputs

# Tokenize input and output data
def tokenize_data(inputs, outputs):
    tokenizer = Tokenizer()
    tokenizer.fit_on_texts(inputs + outputs)
    vocab_size = len(tokenizer.word_index) + 1

    input_sequences = tokenizer.texts_to_sequences(inputs)
    output_sequences = tokenizer.texts_to_sequences(outputs)

    # Print the lengths of input_sequences and output_sequences
    print("Length of input_sequences:", [len(seq) for seq in input_sequences])
    print("Length of output_sequences:", [len(seq) for seq in output_sequences])

    max_len = max(max(len(seq) for seq in input_sequences), max(len(seq) for seq in output_sequences))
    
    input_padded = pad_sequences(input_sequences, maxlen=max_len, padding='post')
    output_padded = pad_sequences(output_sequences, maxlen=max_len, padding='post')

    return input_padded, output_padded, tokenizer, vocab_size, max_len

# Create the model
def create_model(vocab_size, max_len):
    model = Sequential()
    model.add(Embedding(vocab_size, 50, input_length=max_len, trainable=True))
    model.add(LSTM(100))
    model.add(Dense(vocab_size, activation='softmax'))

    model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])

    return model

# Train the model
def train_model(model, input_padded, output_padded, epochs=10):
    model.fit(input_padded, output_padded, epochs=epochs)

# Generate a response
def generate_response(model, tokenizer, input_text, max_len):
    input_seq = tokenizer.texts_to_sequences([input_text])
    input_padded = pad_sequences(input_seq, maxlen=max_len, padding='post')
    predicted_index = np.argmax(model.predict(input_padded), axis=-1)[0]
    return tokenizer.index_word[predicted_index]

# Main function
def main():
    conversations_file = 'movie_conversations.txt'
    lines_file = 'movie_lines.txt'

    inputs, outputs = load_conversation_data(conversations_file, lines_file)
    input_padded, output_padded, tokenizer, vocab_size, max_len = tokenize_data(inputs, outputs)

    # Print the number of conversations, inputs, and outputs
    print("Number of conversations:", len(inputs))
    print("Number of inputs:", len(inputs))
    print("Number of outputs:", len(outputs))

    model = create_model(vocab_size, max_len)
    train_model(model, input_padded, output_padded, epochs=10)

    print("\nChatbot is ready! Type 'exit' to end the conversation.\n")

    while True:
        user_input = input("You: ")
        if user_input.lower() == 'exit':
            break
        response = generate_response(model, tokenizer, user_input, max_len)
        print(f"Chatbot: {response}")

if __name__ == "__main__":
    main()
