# API configuration — blank placeholders

No API keys, tokens, private endpoints or passwords are included.

- GEMINI_API_KEY: add your own Gemini key locally.
- OPENAI_API_KEY: add only if using hosted Whisper or an OpenAI TTS service.
- NOVA_TTS_API_KEY, NOVA_TTS_BASE_URL, NOVA_TTS_MODEL: fill only after confirming the exact Nova voice provider and API.
- WHISPER_MODE: choose api or local after selecting the implementation.

Copy raspberry_pi/.env.example to .env on the Raspberry Pi. The .env file is excluded by .gitignore. Never commit real credentials. If a key was committed, revoke/rotate it; deleting it in a later commit does not make the old key secret.
