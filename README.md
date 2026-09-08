# Local Agents API

A small C client for sending chat requests to a local Ollama server over HTTP.

## Project layout

- `API/inference/ollama.c` - request construction and libcurl HTTP client
- `API/inference/ollama.h` - API declarations
- `API/inference/app` - existing Linux executable

## Requirements

- A running [Ollama](https://ollama.com/) server at `http://localhost:11434`
- A model available to Ollama, configured in `API/inference/ollama.c`
- Development packages for `libcurl` and `cJSON` when building from source

## Usage

Start Ollama, ensure the configured model is available, then run:

```sh
./API/inference/app
```

The client sends a non-streaming chat request to Ollama's `/api/chat` endpoint
and prints the generated request JSON.
