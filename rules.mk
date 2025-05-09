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
CAPS_WORD_ENABLE = yes

# SENTENCE_CASE_ENABLE: Automatically capitalize first letter of sentences
SENTENCE_CASE_ENABLE = yes

# DEFERRED_EXEC_ENABLE: Allow functions to be executed after a delay
DEFERRED_EXEC_ENABLE = yes

# SMTD_ENABLE: Smart Tap Dance extension
SMTD_ENABLE = yes

# TAP_DANCE_ENABLE: Configure keys to have different behavior depending on taps
# TAP_DANCE_ENABLE = yes

# LEADER_ENABLE: Allows for key sequences like Vim leader commands
LEADER_ENABLE = no

# === RGB LIGHTING ===
# RGB_MATRIX_ENABLE: Control per-key RGB LEDs
RGB_MATRIX_ENABLE = yes

# === DEBUGGING AND UTILITY ===
# CONSOLE_ENABLE: Debug console for QMK
CONSOLE_ENABLE = no

# COMMAND_ENABLE: Enable command processing
COMMAND_ENABLE = no