/* See LICENSE file for copyright and license details. */

/* appearance */
// static const char font[]        = "DMCA Sans Serif:pixelsize=13:antialias=true:autohint=true";
// static const char font[]        = "Fantasque Sans Mono:pixelsize=13:antialias=true:autohint=true";
// static const char font[]        = "Fira Code:pixelsize=12:antialias=true:autohint=true";
// static const char font[]        = "Hack:pixelsize=12:antialias=true:autohint=true";
// static const char font[]        = "Inconsolata LGC:pixelsize=12:antialias=true:autohint=true";
static const char font[]        = "Iosevka Custom:pixelsize=13:antialias=true:autohint=true";
// static const char font[]        = "JetBrains Mono NL:pixelsize=12:antialias=true:autohint=true";
// static const char font[]        = "Noto Sans Mono:pixelsize=12:antialias=true:autohint=true";
static const char* normbgcolor  = "#3c3836";
static const char* normfgcolor  = "#928374";
static const char* selbgcolor   = "#282828";
static const char* selfgcolor   = "#d79921";
static const char* urgbgcolor   = "#cc241d";
static const char* urgfgcolor   = "#282828";
static const char before[]      = "<";
static const char after[]       = ">";
static const char titletrim[]   = "...";
static const int  tabwidth      = 125;
static const Bool foreground    = True;
static       Bool urgentswitch  = False;
static const int barHeight      = 21;

/*
 * Where to place a new tab when it is opened. When npisrelative is True,
 * then the current position is changed + newposition. If npisrelative
 * is False, then newposition is an absolute position.
 */
static int  newposition   = 1;
static Bool npisrelative  = True;

#define SETPROP(p) { \
        .v = (char *[]){ "/bin/sh", "-c", \
                "prop=\"`xwininfo -children -id $1 | grep '^     0x' |" \
                "sed -e's@^ *\\(0x[0-9a-f]*\\) \"\\([^\"]*\\)\".*@\\1 \\2@' |" \
                "xargs -0 printf %b | dmenu -l 10 -h 21 -fn \"$2\" -w $1`\" &&" \
                "xprop -id $1 -f $0 8s -set $0 \"$prop\"", \
                p, winid, font, NULL \
        } \
}

#define MODKEY ControlMask
static Key keys[] = {
	/* modifier             key        function     argument */
	{ MODKEY|ShiftMask,     XK_Return, focusonce,   { 0 } },
	{ MODKEY|ShiftMask,     XK_Return, spawn,       { 0 } },

	{ MODKEY|ShiftMask,     XK_l,      rotate,      { .i = +1 } },
	{ MODKEY|ShiftMask,     XK_h,      rotate,      { .i = -1 } },
	{ MODKEY|ShiftMask,     XK_j,      movetab,     { .i = -1 } },
	{ MODKEY|ShiftMask,     XK_k,      movetab,     { .i = +1 } },
	{ MODKEY,               XK_Tab,    rotate,      { .i = 0 } },

	{ MODKEY,               XK_Escape, spawn,       SETPROP("_TABBED_SELECT_TAB") },
	{ MODKEY,               XK_1,      move,        { .i = 0 } },
	{ MODKEY,               XK_2,      move,        { .i = 1 } },
	{ MODKEY,               XK_3,      move,        { .i = 2 } },
	{ MODKEY,               XK_4,      move,        { .i = 3 } },
	{ MODKEY,               XK_5,      move,        { .i = 4 } },
	{ MODKEY,               XK_6,      move,        { .i = 5 } },
	{ MODKEY,               XK_7,      move,        { .i = 6 } },
	{ MODKEY,               XK_8,      move,        { .i = 7 } },
	{ MODKEY,               XK_9,      move,        { .i = 8 } },
	{ MODKEY,               XK_0,      move,        { .i = 9 } },

	{ MODKEY|ShiftMask,     XK_q,      killclient,  { 0 } },

	{ MODKEY,               XK_space,  focusurgent, { 0 } },
	{ MODKEY|ShiftMask,     XK_space,  toggle,      { .v = (void*) &urgentswitch } },

	{ 0,                    XK_F11,    fullscreen,  { 0 } },
};
