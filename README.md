# My QMK Keyboard Configuration

Welcome to the chaotic carnival of my QMK setup 🥳. This repo holds the Frankenstein’s monster of my keyboard firmware—once a single colossal keymap blob, now mercifully split into neat little feature files. Dive in if you dare.

## 🤷‍♀️ What Is This?

A semi–modular, slightly neurotic QMK configuration for my custom mechanical keyboard (shout‑out to the GMMK2 P96 ANSI layout). Packed with home‑row mods, sentence‑case magic, secret‑password macros, virtual‑desktop fu, and more questionable design choices.

## ✨ Features

* **Home‑row Mods** via `sm_td`: tap‑dance your way through GUI/Alt/Shift/Ctrl without finger gymnastics.
* **Sentence Case** auto‑capitalization for those who can’t be bothered to hold Shift.
* **Secret‑macro fortress**: enter a PIN to unlock and spit out passwords or phrases on demand.
* **Virtual Desktop Control**: switch or move windows across desktops with fancy key combos, all without installing software on your host machine.
* **Meta Layer**: OS‑level shortcuts (Win+…), because obviously there aren't enough shortcuts already.
* **RGB Matrix Indicators**: pin status, layer state, Caps‑lock, and function layer glowed to life.

## 🗂️ Repo Structure

```bash
.
├── config.h               # board-specific & pin config
├── custom_keycodes.h      # your secret sauce keycodes
├── features/              # all the broken-out logic
│   ├── sentence_case.*    # auto-capitalization engine
│   ├── sm_td.h            # flexible home-row mods
│   ├── secrets_manager.*  # PIN & password macros
│   ├── virtual_desktop.*  # desktop-switching code
│   ├── rgb_indicators.*   # custom RGB rules
│   └── run_cmds.h         # run dialog helper
├── keymap.c               # glue wiring layers & features
├── keymap.json            # QMK user module imports
├── keymaps.h              # layer & key definitions
├── layers.h               # named layer constants
├── rules.mk               # QMK build flags
└── secrets.h              # (optional) override default PIN/passwords
```

*(The ancient monolithic version lives in our memory—good riddance.)*

## 🛠️ Setup

1. Clone or symlink this folder into your QMK `keyboards/...` directory:

   ```sh
   cd qmk_firmware/keyboards/gmmk2/p96/ansi
   git clone https://github.com/LordHerdier/qmk_config lordherdier
   ```
2. If you need secrets, copy `secrets.h.example` → `secrets.h` and tweak your PIN & phrases.
3. Ensure `rules.mk` options match your needs (RGB\_MATRIX\_ENABLE, etc.).

## 🚧 Build & Flash

```sh
qmk compile -kb gmmk2/p96/ansi -km lordherdier
qmk flash -kb gmmk2/p96/ansi -km lordherdier
```

Or let the QMK Toolbox do its thing if you’re into GUIs.

## 🔧 Customization

* Tweak keycodes in `custom_keycodes.h`.
* Add or rip out feature files under `features/`.
* Layers & combos live in `keymap.c`—beware of pointer juggling.
* RGB tweaks in `rgb_indicators.c` if you crave more disco.

## 🐛 Contributing

Feel free to fork this repo and make your own changes. This is a personal configuration though, so I probably won't merge any PRs.

## 📜 License

This mess is licensed under GPLv2. Go nuts, but keep it GPLv2.


