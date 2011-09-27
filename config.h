/* modifier 0 means no modifier */
static char *useragent      = "Surf/"VERSION" (X11; U; Unix; en-US) AppleWebKit/531.2+ Compatible (Safari)";
static char *progress       = "#FF0000";
static char *progress_trust = "#00FF00";
static char *stylefile      = ".surf/style.css";
static char *scriptfile     = ".surf/script.js";
static char *cookiefile     = ".surf/cookies.txt";
static char *historyfile    = ".surf/history";
static time_t sessiontime   = 3600;

static SearchEngine searchengines[] = {
  { "g",   "http://www.google.com/search?q=%s" },
  { "gc",   "http://google.com/codesearch?hl=en&lr=&q=%s" },
  { "gtr", "http://google.com/search?q=%s&lr=lang_tr" },

  { "w",   "http://en.wikipedia.org/w/index.php?title=Special:Search&search=%s&go=Go" },

  { "dl", "http://del.icio.us/xingjiangao/%s" },
  { "dp", "http://delicious.com/popular/%s" },
  { "ds", "http://delicious.com/search?p=%s&chk=&context=userposts|xingjiangao&fr=del_icio_us&lc=1" },

  { "so", "http://google.com/search?hl=en&safe=off&num=100&q=site:stackoverflow.com+%s&aq=f&oq=&aqi=" },
  { "dict", "http://www.google.com/#q=%s&tbs=dfn:1" },
  { "lastfm", "http://last.fm/music/%s" },
  { "flickr", "http://flickr.com/search/?q=%s&m=tags&s=int" },
  { "garanti", "https://sube.garanti.com.tr/isube/loginform" },
  { "eksi", "http://sozluk.sourtimes.org/show.asp?t=%s" },
  { "zargan", "http://zargan.com/sozluk.asp?Sozcuk=%s" },
  { "ddg",   "http://www.duckduckgo.com/?q=%s" },
  { "wa",   "http://www.wolframalpha.com/input/?i=%s" },
  { "imdb",   "http://google.com/search?q=site:imdb.com%20%s&num=100" }
};

#define HIDE_BACKGROUND FALSE
#define HOMEPAGE "http://localhost/dashboard"
#define MODKEY GDK_CONTROL_MASK

#define SETPROP(p, q)     { .v = (char *[]){ "/bin/sh", "-c", \
	"prop=\"`xprop -id $2 $0 | cut -d '\"' -f 2 | surf_br_history`\" &&" \
  ". /home/azer/.surf/clean_history.sh &&"\
	"xprop -id $2 -f $1 8s -set $1 \"$prop\"", \
	p, q, winid, NULL } }

#define DOWNLOAD(d) { \
	.v = (char *[]){ "/bin/sh", "-c", \
	"xterm -e \"wget --load-cookies ~/.surf/cookies.txt '$0';\"", \
	d, NULL } }

#define SETURI(p)       { .v = (char *[]){ "/bin/sh", "-c", \
"prop=\"`dmenu`\" &&" \
"xprop -id $1 -f $0 8s -set $0 \"$prop\"", \
p, winid, NULL } }

#define ADDBMK           { .v = (char *[]){ "/bin/sh", "-c", \
    "surf-bk-add $0", winid, NULL } }

#define LOADBMK(p)       { .v = (char *[]){ "/bin/sh", "-c", \
        "xprop -id $1 -f $0 8s -set $0 `bk_browse` || exit 0", \
     p, winid, NULL } }

static Key keys[] = {
    /* modifier	            keyval      function    arg             Focus */
    { MODKEY|GDK_SHIFT_MASK,GDK_r,      reload,     { .b = TRUE } },
    { MODKEY,               GDK_r,      reload,     { .b = FALSE } },
    { MODKEY|GDK_SHIFT_MASK,GDK_p,      print,      { 0 } },
    { MODKEY,               GDK_p,      clipboard,  { .b = TRUE } },
    { MODKEY,               GDK_y,      clipboard,  { .b = FALSE } },
    { MODKEY|GDK_SHIFT_MASK,GDK_j,      zoom,       { .i = -1 } },
    { MODKEY|GDK_SHIFT_MASK,GDK_k,      zoom,       { .i = +1 } },
    { MODKEY|GDK_SHIFT_MASK,GDK_i,      zoom,       { .i = 0  } },
    { MODKEY,               GDK_l,      navigate,   { .i = +1 } },
    { MODKEY,               GDK_h,      navigate,   { .i = -1 } },
    { MODKEY,               GDK_j,      scroll,     { .i = +1 } },
    { MODKEY,               GDK_k,      scroll,     { .i = -1 } },
    { 0,                    GDK_Escape, stop,       { 0 } },
    { MODKEY,               GDK_o,      source,     { 0 } },
    { MODKEY,               GDK_g,      spawn,      SETPROP("_SURF_URI", "_SURF_GO") },
    { MODKEY,               GDK_f,      spawn,      SETPROP("_SURF_FIND", "_SURF_FIND") },
    { MODKEY,               GDK_n,      find,       { .b = TRUE } },
    { MODKEY,               GDK_Return, spawn,      SETURI("_SURF_URI") },
    { MODKEY,               GDK_a,      spawn,      ADDBMK },
    { MODKEY,               GDK_b,      spawn,      LOADBMK("_SURF_URI") },
    { MODKEY|GDK_SHIFT_MASK,GDK_n,      find,       { .b = FALSE } },
};

