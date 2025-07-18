############################
# QMK FIRMWARE CONFIG
############################

# === CUSTOM FEATURES AND SOURCE FILES ===
# Add custom C files to be compiled
SRC += features/sentence_case.c      # Sentence case implementation
SRC += features/secrets_manager.c    # Secure storage for sensitive data
SRC += features/virtual_desktop.c    # Virtual desktop switching functionality
SRC += features/rgb_indicators.c     # RGB lighting status indicators

# === CORE QMK FEATURES ===
# CAPS_WORD_ENABLE: Type words in all caps by tapping shift+shift
# This also automatically shifts - to _ so you can type things like EXAMPLE_TEXT easily
# See https://docs.qmk.fm/features/caps_word
CAPS_WORD_ENABLE = yes
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD # Enable this to make both shift keys activate caps word

# SENTENCE_CASE_ENABLE: Automatically capitalize first letter of sentences
SENTENCE_CASE_ENABLE = yes

# DYNAMIC_TAPPING_TERM_ENABLE: Adjust tapping term at runtime with DT_PRNT, DT_UP, and DT_DOWN (see keymaps.c for usage)
DYNAMIC_TAPPING_TERM_ENABLE = yes

# DEFERRED_EXEC_ENABLE: Allow functions to be executed after a delay
DEFERRED_EXEC_ENABLE = yes

# AUTOCORRECT_ENABLE = yes

# TAP_DANCE_ENABLE: Configure keys to have different behavior depending on taps
# I was was using this for some custom keys at one point, but I don't think I need it anymore
# If you want to add tap dance functionality, you can enable this
# and define your tap dance keycodes in custom_keycodes.h and keymaps.c

# TAP_DANCE_ENABLE = yes

# LEADER_ENABLE: Allows for key sequences like Vim leader commands
# Might revisit this in the future, but for now I don't use it
LEADER_ENABLE = no

# === RGB LIGHTING ===
# RGB_MATRIX_ENABLE: Control per-key RGB LEDs
RGB_MATRIX_ENABLE = yes

# === DEBUGGING AND UTILITY ===
# CONSOLE_ENABLE: Debug console for QMK
CONSOLE_ENABLE = no

# COMMAND_ENABLE: Enable command processing
COMMAND_ENABLE = no

