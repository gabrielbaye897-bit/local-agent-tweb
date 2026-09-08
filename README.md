# Local Agents API

A small C client for sending chat requests to a local Ollama server over HTTP.

## Project layout

- `API/inference/ollama.c` - request construction and libcurl HTTP client
- `API/inference/ollama.h` - API declarations
- `API/inference/app` - existing Linux executable

## Requirements

### Current backend: Ollama

- A running [Ollama](https://ollama.com/) server at `http://localhost:11434`
- A model available to Ollama, configured in `API/inference/ollama.c`
- Development packages for `libcurl` and `cJSON` when building from source

### Planned backend options

The inference layer is intended to support more than a local Ollama server:

- Your own AI API, provided through a compatible HTTP endpoint
- A hosted model from [Hugging Face](https://huggingface.co/models)
- A locally downloaded Hugging Face model, when a suitable local inference
  runtime is added

At the moment, the example client is wired to Ollama only. These alternatives
will require an adapter or endpoint configuration in the inference layer.

## Usage

Start Ollama, ensure the configured model is available, then run:

```sh
./API/inference/app
```

The client sends a non-streaming chat request to Ollama's `/api/chat` endpoint
and prints the generated request JSON.
