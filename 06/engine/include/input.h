#pragma once
#include "SDL3/SDL_keycode.h"
#include <vector>

enum KeyCode
{
    Unknown              = SDLK_UNKNOWN,
    Backspace            = SDLK_BACKSPACE,
    Tab                  = SDLK_TAB,
    Enter                = SDLK_RETURN,
    Escape               = SDLK_ESCAPE,
    Space                = SDLK_SPACE,
    ExclamationMark      = SDLK_EXCLAIM,
    DoubleQuote          = SDLK_QUOTEDBL,
    Hash                 = SDLK_HASH,
    Dollar               = SDLK_DOLLAR,
    Percent              = SDLK_PERCENT,
    Ampersand            = SDLK_AMPERSAND,
    Quote                = SDLK_QUOTE,
    LeftParenthesis      = SDLK_LEFTPAREN,
    RightParenthesis     = SDLK_RIGHTPAREN,
    Asterisk             = SDLK_ASTERISK,
    Plus                 = SDLK_PLUS,
    Comma                = SDLK_COMMA,
    Minus                = SDLK_MINUS,
    Period               = SDLK_PERIOD,
    ForwardSlash         = SDLK_SLASH,
    Num0                 = SDLK_0,
    Num1                 = SDLK_1,
    Num2                 = SDLK_2,
    Num3                 = SDLK_3,
    Num4                 = SDLK_4,
    Num5                 = SDLK_5,
    Num6                 = SDLK_6,
    Num7                 = SDLK_7,
    Num8                 = SDLK_8,
    Num9                 = SDLK_9,
    Colon                = SDLK_COLON,
    Semicolon            = SDLK_SEMICOLON,
    LessThan             = SDLK_LESS,
    Equals               = SDLK_EQUALS,
    GreaterThan          = SDLK_GREATER,
    QuestionMark         = SDLK_QUESTION,
    At                   = SDLK_AT,
    LeftBracket          = SDLK_LEFTBRACKET,
    Backslash            = SDLK_BACKSLASH,
    RightBracket         = SDLK_RIGHTBRACKET,
    Caret                = SDLK_CARET,
    Underscore           = SDLK_UNDERSCORE,
    Backquote            = SDLK_BACKQUOTE,
    A                    = SDLK_a,
    B                    = SDLK_b,
    C                    = SDLK_c,
    D                    = SDLK_d,
    E                    = SDLK_e,
    F                    = SDLK_f,
    G                    = SDLK_g,
    H                    = SDLK_h,
    I                    = SDLK_i,
    J                    = SDLK_j,
    K                    = SDLK_k,
    L                    = SDLK_l,
    M                    = SDLK_m,
    N                    = SDLK_n,
    O                    = SDLK_o,
    P                    = SDLK_p,
    Q                    = SDLK_q,
    R                    = SDLK_r,
    S                    = SDLK_s,
    T                    = SDLK_t,
    U                    = SDLK_u,
    V                    = SDLK_v,
    W                    = SDLK_w,
    X                    = SDLK_x,
    Y                    = SDLK_y,
    Z                    = SDLK_z,
    CapsLock             = SDLK_CAPSLOCK,
    F1                   = SDLK_F1,
    F2                   = SDLK_F2,
    F3                   = SDLK_F3,
    F4                   = SDLK_F4,
    F5                   = SDLK_F5,
    F6                   = SDLK_F6,
    F7                   = SDLK_F7,
    F8                   = SDLK_F8,
    F9                   = SDLK_F9,
    F10                  = SDLK_F10,
    F11                  = SDLK_F11,
    F12                  = SDLK_F12,
    PrintScreen          = SDLK_PRINTSCREEN,
    ScrollLock           = SDLK_SCROLLLOCK,
    Pause                = SDLK_PAUSE,
    Insert               = SDLK_INSERT,
    Home                 = SDLK_HOME,
    PageUp               = SDLK_PAGEUP,
    Delete               = SDLK_DELETE,
    End                  = SDLK_END,
    PageDown             = SDLK_PAGEDOWN,
    Right                = SDLK_RIGHT,
    Left                 = SDLK_LEFT,
    Down                 = SDLK_DOWN,
    Up                   = SDLK_UP,
    NumLockClear         = SDLK_NUMLOCKCLEAR,
    KeypadDivide         = SDLK_KP_DIVIDE,
    KeypadMultiply       = SDLK_KP_MULTIPLY,
    KeypadMinus          = SDLK_KP_MINUS,
    KeypadPlus           = SDLK_KP_PLUS,
    KeypadEnter          = SDLK_KP_ENTER,
    KeypadDecimal        = SDLK_KP_DECIMAL,
    Application          = SDLK_APPLICATION,
    Power                = SDLK_POWER,
    KeypadEquals         = SDLK_KP_EQUALS,
    F13                  = SDLK_F13,
    F14                  = SDLK_F14,
    F15                  = SDLK_F15,
    F16                  = SDLK_F16,
    F17                  = SDLK_F17,
    F18                  = SDLK_F18,
    F19                  = SDLK_F19,
    F20                  = SDLK_F20,
    F21                  = SDLK_F21,
    F22                  = SDLK_F22,
    F23                  = SDLK_F23,
    F24                  = SDLK_F24,
    Execute              = SDLK_EXECUTE,
    Help                 = SDLK_HELP,
    Menu                 = SDLK_MENU,
    Select               = SDLK_SELECT,
    Stop                 = SDLK_STOP,
    Again                = SDLK_AGAIN,
    Undo                 = SDLK_UNDO,
    Cut                  = SDLK_CUT,
    Copy                 = SDLK_COPY,
    Paste                = SDLK_PASTE,
    Find                 = SDLK_FIND,
    Mute                 = SDLK_MUTE,
    VolumeUp             = SDLK_VOLUMEUP,
    VolumeDown           = SDLK_VOLUMEDOWN,
    KeypadComma          = SDLK_KP_COMMA,
    KeypadEqualsAs400    = SDLK_KP_EQUALSAS400,
    Alterase             = SDLK_ALTERASE,
    Sysreq               = SDLK_SYSREQ,
    Cancel               = SDLK_CANCEL,
    Clear                = SDLK_CLEAR,
    Prior                = SDLK_PRIOR,
    Return2              = SDLK_RETURN2,
    Separator            = SDLK_SEPARATOR,
    Out                  = SDLK_OUT,
    Oper                 = SDLK_OPER,
    ClearAgain           = SDLK_CLEARAGAIN,
    CrSel                = SDLK_CRSEL,
    ExSel                = SDLK_EXSEL,
    Keypad00             = SDLK_KP_00,
    Keypad000            = SDLK_KP_000,
    ThousandsSeparator   = SDLK_THOUSANDSSEPARATOR,
    DecimalSeparator     = SDLK_DECIMALSEPARATOR,
    CurrencyUnit         = SDLK_CURRENCYUNIT,
    CurrencySubunit      = SDLK_CURRENCYSUBUNIT,
    KeypadLeftParen      = SDLK_KP_LEFTPAREN,
    KeypadRightParen     = SDLK_KP_RIGHTPAREN,
    KeypadLeftBrace      = SDLK_KP_LEFTBRACE,
    KeypadRightBrace     = SDLK_KP_RIGHTBRACE,
    KeypadTab            = SDLK_KP_TAB,
    KeypadBackspace      = SDLK_KP_BACKSPACE,
    KeypadA              = SDLK_KP_A,
    KeypadB              = SDLK_KP_B,
    KeypadC              = SDLK_KP_C,
    KeypadD              = SDLK_KP_D,
    KeypadE              = SDLK_KP_E,
    KeypadF              = SDLK_KP_F,
    KeypadXor            = SDLK_KP_XOR,
    KeypadPower          = SDLK_KP_POWER,
    KeypadPercent        = SDLK_KP_PERCENT,
    KeypadLess           = SDLK_KP_LESS,
    KeypadGreater        = SDLK_KP_GREATER,
    KeypadAmpersand      = SDLK_KP_AMPERSAND,
    KeypadDblAmpersand   = SDLK_KP_DBLAMPERSAND,
    KeypadVerticalBar    = SDLK_KP_VERTICALBAR,
    KeypadDblVerticalBar = SDLK_KP_DBLVERTICALBAR,
    KeypadColon          = SDLK_KP_COLON,
    KeypadHash           = SDLK_KP_HASH,
    KeypadSpace          = SDLK_KP_SPACE,
    KeypadAT             = SDLK_KP_AT,
    KeyPadExclam         = SDLK_KP_EXCLAM,
    KeyPadMemStore       = SDLK_KP_MEMSTORE,
    KeyPadMemRecall      = SDLK_KP_MEMRECALL,
    KeyPadMemClear       = SDLK_KP_MEMCLEAR,
    KeyPadMemAdd         = SDLK_KP_MEMADD,
    KeyPadMemSubtract    = SDLK_KP_MEMSUBTRACT,
    KeyPadMemMultiply    = SDLK_KP_MEMMULTIPLY,
    KeyPadMemDivide      = SDLK_KP_MEMDIVIDE,
    KeyPadPlusMinus      = SDLK_KP_PLUSMINUS,
    KeyPadClear          = SDLK_KP_CLEAR,
    KeyPadClearEntry     = SDLK_KP_CLEARENTRY,
    KeyPadBinary         = SDLK_KP_BINARY,
    KeyPadOctal          = SDLK_KP_OCTAL,
    KeyPadDecimal        = SDLK_KP_DECIMAL,
    KeyPadHexDecimal     = SDLK_KP_HEXADECIMAL,
    LeftControl          = SDLK_LCTRL,
    LeftShift            = SDLK_LSHIFT,
    LeftAlt              = SDLK_LALT,
    LeftGUI              = SDLK_LGUI,
    RightControl         = SDLK_RCTRL,
    RightShift           = SDLK_RSHIFT,
    RightAlt             = SDLK_RALT,
    RightGUI             = SDLK_RGUI,
    Mode                 = SDLK_MODE,
    AudioNext            = SDLK_AUDIONEXT,
    AudioPrev            = SDLK_AUDIOPREV,
    AudioStop            = SDLK_AUDIOSTOP,
    AudioPlay            = SDLK_AUDIOPLAY,
    AudioMute            = SDLK_AUDIOMUTE,
    MediaSelect          = SDLK_MEDIASELECT,
    WWW                  = SDLK_WWW,
    Mail                 = SDLK_MAIL,
    Calculator           = SDLK_CALCULATOR,
    Computer             = SDLK_COMPUTER,
    ACSearch             = SDLK_AC_SEARCH,
    ACHome               = SDLK_AC_HOME,
    ACBack               = SDLK_AC_BACK,
    ACForward            = SDLK_AC_FORWARD,
    ACStop               = SDLK_AC_STOP,
    ACRefresh            = SDLK_AC_REFRESH,
    ACBookmarks          = SDLK_AC_BOOKMARKS,
    BrightessDown        = SDLK_BRIGHTNESSDOWN,
    BrightnessUp         = SDLK_BRIGHTNESSUP,
    DisplaySwitch        = SDLK_DISPLAYSWITCH,
    KBDillumToggle       = SDLK_KBDILLUMTOGGLE,
    KBDillumDown         = SDLK_KBDILLUMDOWN,
    KBDillumUp           = SDLK_KBDILLUMUP,
    Eject                = SDLK_EJECT,
    Sleep                = SDLK_SLEEP,
    App1                 = SDLK_APP1,
    App2                 = SDLK_APP2,
    AudioRewind          = SDLK_AUDIOREWIND,
    AudioFastForward     = SDLK_AUDIOFASTFORWARD,
    SoftLeft             = SDLK_SOFTLEFT,
    SoftRight            = SDLK_SOFTRIGHT,
    Call                 = SDLK_CALL,
    EndCall              = SDLK_ENDCALL
};
class Input
{
public:
    static std::vector<KeyCode> button;
    static std::vector<KeyCode> buttonUp;
    static std::vector<KeyCode> buttonDown;
    static std::vector<uint8_t> mouseButton;
    static std::vector<uint8_t> mouseButtonUp;
    static std::vector<uint8_t> mouseButtonDown;

    static bool GetKeyDown(KeyCode key);
    static bool GetKey(KeyCode key);
    static bool GetKeyUp(KeyCode key);
    static bool GetMouseButtonDown(uint8_t mouse);
    static bool GetMouseButton(uint8_t mouse);
    static bool GetMouseButtonUp(uint8_t mouse);
};