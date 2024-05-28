def custom_lz77_encode(input_string, buffer_size):
    if not input_string:
        return ""

    # Initialize the search buffer with the first character
    search_buffer = input_string[0]
    # Initialize the lookahead buffer with the next few characters
    lookahead_buffer = input_string[1:1 + buffer_size]
    encoded_output = []

    # Start encoding
    i = 1 + buffer_size
    while i <= len(input_string) or lookahead_buffer:
        match_found = False
        # Check for matches in the search buffer
        for j in range(len(lookahead_buffer)):
            if lookahead_buffer[j] in search_buffer:
                encoded_output.append(lookahead_buffer[j])
                # Shift buffers
                search_buffer += lookahead_buffer[j]
                search_buffer = search_buffer[-buffer_size:]  # Keep search buffer size fixed
                i += j + 1
                match_found = True
                # Update lookahead buffer
                lookahead_buffer = input_string[i:i + buffer_size]
                break

        if not match_found:
            # If no match found, just move the buffers forward
            if lookahead_buffer:
                encoded_output.append(lookahead_buffer[0])
                search_buffer += lookahead_buffer[0]
                search_buffer = search_buffer[-buffer_size:]  # Keep search buffer size fixed
                i += 1
                # Update lookahead buffer
                lookahead_buffer = input_string[i:i + buffer_size]

        # Break if we've processed the entire input string and the lookahead buffer is empty
        if i > len(input_string) and not lookahead_buffer:
            break

    return ''.join(encoded_output)


# Example usage
input_string = "aacaacabcabaaac"
buffer_size = 5
encoded_string = custom_lz77_encode(input_string, buffer_size)
print("Encoded String:", encoded_string)
