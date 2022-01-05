/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]        = "Iosevka Nerd Font:size=11:antialias=true:autohint=true";
static const char* normbgcolor  = "#192e40";
static const char* normfgcolor  = "#fff6e6";
static const char* selbgcolor   = "#0b1726";
static const char* selfgcolor   = "#e9986d";
static const char* urgbgcolor   = "#c20f47";
static const char* urgfgcolor   = "#0b1726";
static const char before[]      = "";
static const char after[]       = "";
static const char titletrim[]   = "...";
static const int  tabwidth      = 125;
static const Bool foreground    = True;
static       Bool urgentswitch  = False;
static const int barHeight      = 25;

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
                "xargs -0 printf %b | dmenu -l 10 -w $1`\" &&" \
                "xprop -id $1 -f $0 8s -set $0 \"$prop\"", \
                p, winid, NULL \
        } \
}

#define MODKEY Mod1Mask
static Key keys[] = {
	/* modifier             key        function     argument */
	{ MODKEY|ShiftMask,     XK_Return, focusonce,   { 0 } },
	{ MODKEY|ShiftMask,     XK_Return, spawn,       { 0 } },

	{ MODKEY,               XK_l,      rotate,      { .i = +1 } },
	{ MODKEY,               XK_h,      rotate,      { .i = -1 } },
	{ MODKEY|ShiftMask,     XK_h,      movetab,     { .i = -1 } },
	{ MODKEY|ShiftMask,     XK_l,      movetab,     { .i = +1 } },
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
	// { MODKEY,               XK_0,      move,        { .i = 9 } }, // already used to reset zoom in st

	{ MODKEY|ShiftMask,     XK_q,      killclient,  { 0 } },

	{ MODKEY,               XK_x,      focusurgent, { 0 } },
	{ MODKEY|ShiftMask,     XK_x,      toggle,      { .v = (void*) &urgentswitch } },

	{ 0,                    XK_F11,    fullscreen,  { 0 } },
};
