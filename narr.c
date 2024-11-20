// fsubs.c
#include "ftale.h"

//  ;max 36 for scroll
//  ;max 29 for placard
//  ;% = character name
//  ;$ = who we are speaking to??
//
//                  dseg
//                  public  _place_msg,_inside_msg,_place_tbl,_inside_tbl
//                  public  _event_msg
//
//                  public  _print_cont
//  _event_msg
//                  dc.b    "% was getting rather hungry.",0
//                  dc.b    "% was getting very hungry.",0
//                  dc.b    "% was starving!",0
//                  dc.b    "% was getting tired.",0
//                  dc.b    "% was getting sleepy.",0
//  ; 5
//                  dc.b    '% was hit and killed!',0
//                  dc.b    '% was drowned in the water!',0
//                  dc.b    '% was burned in the lava.',0
//                  dc.b    '% was turned to stone by the witch.',0
//                  dc.b    '% started the journey in his home village of Tambry',0
//  ; 10
//                  dc.b    'as had his brother before him.',0
//                  dc.b    'as had his brothers before him.',0
//                  dc.b    "% just couldn't stay awake any longer!",0
//                  dc.b    '% was feeling quite full.',0
//                  dc.b    '% was feeling quite rested.',0
//  ; 15
//                  dc.b    'Even % would not be stupid enough to draw weapon in here.',0
//                  dc.b    'A great calming influence comes over %, preventing him from drawing his weapon.',0
//                  dc.b    '% picked up a scrap of paper.',0
//                  dc.b    'It read: "Find the turtle!"',0
//                  dc.b    'It read: "Meet me at midnight at the Crypt. Signed, the Wraith Lord."',0
//  ; 20
//                  dc.b    '% looked around but discovered nothing.',0
//                  dc.b    '% does not have that item.',0
//                  dc.b    '% bought some food and ate it.',0
//                  dc.b    '% bought some arrows.',0
//                  dc.b    '% passed out from hunger!',0
//  ; 25
//                  dc.b    '% is not sleepy.',0
//                  dc.b    '% was tired, so he decided to lie down and sleep.',0
//                  dc.b    '% perished in the hot lava!',0
//                  dc.b    'It was midnight.',0
//                  dc.b    'It was morning.',0
//  ; 30
//                  dc.b    'It was midday.',0
//                  dc.b    'Evening was drawing near.',0
//                  dc.b    'Ground is too hot for swan to land.',0
//                  dc.b    'Flying too fast to dismount.',0
//                  dc.b    '"They',"'",'re all dead!" he cried.',0
//  ; 35
//                  dc.b    'No time for that now!',0
//                  dc.b    '% put an apple away for later.',0
//                  dc.b    '% ate one of his apples.',0
//                  dc.b    '% discovered a hidden object.',0
//  ; what if monster attacks you when you are sleeping?
//

char event_msg[] =
    "% was getting rather hungry.\0"
    "% was getting very hungry.\0"
    "% was starving!\0"
    "% was getting tired.\0"
    "% was getting sleepy.\0"
    // 5
    "% was hit and killed!\0"
    "% was drowned in the water!\0"
    "% was burned in the lava.\0"
    "% was turned to stone by the witch.\0"
    "% started the journey in his home village of Tambry\0"
    // 10
    "as had his brother before him.\0"
    "as had his brothers before him.\0"
    "% just couldn't stay awake any longer!\0"
    "% was feeling quite full.\0"
    "% was feeling quite rested.\0"
    // 15
    "Even % would not be stupid enough to draw weapon in here.\0"
    "A great calming influence comes over %, preventing him from drawing his weapon.\0"
    "% picked up a scrap of paper.\0"
    "It read: \"Find the turtle!\"\0"
    "It read: \"Meet me at midnight at the Crypt. Signed, the Wraith Lord.\"\0"
    // 20
    "% looked around but discovered nothing.\0"
    "% does not have that item.\0"
    "% bought some food and ate it.\0"
    "% bought some arrows.\0"
    "% passed out from hunger!\0"
    // 25
    "% is not sleepy.\0"
    "% was tired, so he decided to lie down and sleep.\0"
    "% perished in the hot lava!\0"
    "It was midnight.\0"
    "It was morning.\0"
    // 30
    "It was midday.\0"
    "Evening was drawing near.\0"
    "Ground is too hot for swan to land.\0"
    "Flying too fast to dismount.\0"
    "\"They're all dead!\" he cried.\0"
    // 35
    "No time for that now!\0"
    "% put an apple away for later.\0"
    "% ate one of his apples.\0"
    "% discovered a hidden object.\0";
// what if monster attacks you when you are sleeping?

//                 cseg
//                 public   _question
//
//  _question
//                  move.l  4(sp),d0
//                  add.w   d0,d0
//                  add.w   d0,d0
//                  lea     qq,a0
//                  add.l   (a0,d0),a0
//                  move.l  a0,4(sp)
//                  jmp     _print_cont
//
//  qq              dc.l    q1-qq,q2-qq,q3-qq,q4-qq,q5-qq,q6-qq,q7-qq,q8-qq
//
//  q1              dc.b    'To Quest for the...?',0
//  q2              dc.b    'Make haste, but take...?',0
//  q3              dc.b    'Scorn murderous...?',0
//  q4              dc.b    'Summon the...?',0
//  q5              dc.b    'Wing forth in...?',0
//  q6              dc.b    'Hold fast to your...?',0
//  q7              dc.b    'Defy Ye that...?',0
//  q8              dc.b    'In black darker than...?',0
//                  dc.w    0

// question - print copy protection question q
void question(int32_t q)
{
    static char * qq[8] = {"To Quest for the...?",
                           "Make haste, but take...?",
                           "Scorn murderous...?",
                           "Summon the...?",
                           "Wing forth in...?",
                           "Hold fast to your...?",
                           "Defy Ye that...?",
                           "In black darker than...?"};
    print_cont(qq[q]);
}

//                  dseg
//
//  place_tbl
//                  dc.b    51,51,19                ; small keep
//                  dc.b    64,69,02                ; village
//                  dc.b    70,73,03                ; vermillion
//                  dc.b    80,95,06                ; marheim
//                  dc.b    96,99,07                ; witch castle
//                  dc.b    138,139,08              ; graveyard
//                  dc.b    144,144,09              ; stone ring
//                  dc.b    147,147,10              ; lighthouse
//                  dc.b    148,148,20              ; small castle
//                  dc.b    159,162,17              ; desert city
//                  dc.b    163,163,18              ; desert fort
//                  dc.b    164,167,12              ; crystal
//                  dc.b    168,168,21              ; log cabin
//                  dc.b    170,170,22              ; dark fort
//                  dc.b    171,174,14              ; doom tower
//                  dc.b    176,176,13              ; pixie shrine
//                  dc.b    178,178,23              ; swamp cabin
//                  dc.b    179,179,24              ; tomb
//                  dc.b    180,180,25              ; unreachable castle
//                  dc.b    175,180,0               ; lava / elf - nil
//                  dc.b    208,221,11              ; swamp
//                  dc.b    243,243,16              ; oasis
//                  dc.b    250,252,0               ; nil (interface)
//                  dc.b    255,255,26              ; dragon cave
//                  dc.b    78,78,04                ; by mountain type
//                  dc.b    187,239,04              ; by mountain type
//                  dc.b    0,79,0                  ; nil
//                  dc.b    185,254,15              ; desert
//                  dc.b    0,255,0                 ; nil


uint8_t place_tbl[] = {
    51,  51,  19,        // small keep
    64,  69,  2,         // village
    70,  73,  3,         // vermillion
    80,  95,  6,         // marheim
    96,  99,  7,         // witch castle
    138, 139, 8,         // graveyard
    144, 144, 9,         // stone ring
    147, 147, 10,        // lighthouse
    148, 148, 20,        // small castle
    159, 162, 17,        // desert city
    163, 163, 18,        // desert fort
    164, 167, 12,        // crystal
    168, 168, 21,        // log cabin
    170, 170, 22,        // dark fort
    171, 174, 14,        // doom tower
    176, 176, 13,        // pixie shrine
    178, 178, 23,        // swamp cabin
    179, 179, 24,        // tomb
    180, 180, 25,        // unreachable castle
    175, 180, 0,         // lava / elf - nil
    208, 221, 11,        // swamp
    243, 243, 16,        // oasis
    250, 252, 0,         // nil (interface)
    255, 255, 26,        // dragon cave
    78,  78,  4,         // by mountain type
    187, 239, 4,         // by mountain type
    0,   79,  0,         // nil
    185, 254, 15,        // desert
    0,   255, 0          // nil
};

//
//  _inside_tbl
//                  dc.b    2,2,02                  ; small chamber
//                  dc.b    7,7,03                  ; large chamber
//                  dc.b    4,4,04                  ; long passageway
//                  dc.b    5,6,05                  ; twisting tunnel
//                  dc.b    9,10,06                 ; forked intersection
//                  dc.b    30,30,07                ; keep interior - ITEMIZE??
//                  dc.b    19,33,14                ; stone corridor
//                  dc.b    101,101,14              ; stone corridor
//                  dc.b    130,134,14              ; stone corridor
//                  dc.b    36,36,13                ; octagonal room
//                  dc.b    37,42,12                ; large room
//                  dc.b    46,46,0                 ; final arena - special message
//                  dc.b    43,59,11                ; spirit world
//                  dc.b    100,100,11              ; spirit world
//                  dc.b    143,149,11              ; spirit world
//                  dc.b    62,62,16                ; small building
//                  dc.b    65,66,18                ; tavern
//                  dc.b    60,78,17                ; building
//                  dc.b    82,82,17                ; building
//                  dc.b    86,87,17                ; building
//                  dc.b    92,92,17                ; priest's building
//                  dc.b    94,95,17                ; small buildings
//                  dc.b    97,99,17                ; building
//                  dc.b    120,120,17              ; building (desfort)
//                  dc.b    116,119,17              ; building (desert)
//                  dc.b    139,141,17              ; building (desert)
//                  dc.b    79,96,09                ; palace of king mar
//                  dc.b    104,104,19              ; inn
//                  dc.b    114,114,20              ; tomb inside
//                  dc.b    105,115,08              ; castle - ITEMIZE??
//                  dc.b    135,138,08              ; castle (doom tower)
//                  dc.b    125,125,21              ; cabin inside
//                  dc.b    127,127,10              ; elf glade inside
//                  dc.b    142,142,22              ; unlocked/lighthouse
//                  dc.b    121,129,22              ; unlocked/entered
//                  dc.b    150,161,15              ; stone maze
//                  dc.b    0,255,0                 ; nil

UBYTE inside_tbl[] = {
    2,   2,   2,         // small chamber
    7,   7,   3,         // large chamber
    4,   4,   4,         // long passageway
    5,   6,   5,         // twisting tunnel
    9,   10,  6,         // forked intersection
    30,  30,  7,         // keep interior - ITEMIZE??
    19,  33,  14,        // stone corridor
    101, 101, 14,        // stone corridor
    130, 134, 14,        // stone corridor
    36,  36,  13,        // octagonal room
    37,  42,  12,        // large room
    46,  46,  0,         // final arena - special message
    43,  59,  11,        // spirit world
    100, 100, 11,        // spirit world
    143, 149, 11,        // spirit world
    62,  62,  16,        // small building
    65,  66,  18,        // tavern
    60,  78,  17,        // building
    82,  82,  17,        // building
    86,  87,  17,        // building
    92,  92,  17,        // priest's building
    94,  95,  17,        // small buildings
    97,  99,  17,        // building
    120, 120, 17,        // building (desfort)
    116, 119, 17,        // building (desert)
    139, 141, 17,        // building (desert)
    79,  96,  9,         // palace of king mar
    104, 104, 19,        // inn
    114, 114, 20,        // tomb inside
    105, 115, 8,         // castle - ITEMIZE??
    135, 138, 8,         // castle (doom tower)
    125, 125, 21,        // cabin inside
    127, 127, 10,        // elf glade inside
    142, 142, 22,        // unlocked/lighthouse
    121, 129, 22,        // unlocked/entered
    150, 161, 15,        // stone maze
    0,   255, 0          // nil
};

//  ; string macros
//  ; @ = ' entered the '
//  ; # = ' came to '
//  ; $ = 'the '
//  ; ^ = ' castle'
//  ; [ = ' of '
//  ; % = substitute character name
//
//  _place_msg
//                  dc.b    0        ; no message
//                  dc.b    0        ; do not change
//                  dc.b    "% returned to the village of Tambry.",0
//                  dc.b    "% came to Vermillion Manor.",0
//                  dc.b    "% reached the Mountains of Frost",0
//  ; 5
//                  dc.b    "% reached the Plain of Grief.",0
//                  dc.b    "% came to the city of Marheim.",0
//                  dc.b    "% came to the Witch's castle.",0
//                  dc.b    "% came to the Graveyard.",0
//                  dc.b    "% came to a great stone ring.",0
//  ; 10
//                  dc.b    "% came to a watchtower.",0
//                  dc.b    "% traveled to the great Bog.",0
//                  dc.b    "% came to the Crystal Palace.",0
//                  dc.b    "% came to mysterious Pixle Grove.",0
//                  dc.b    "% entered the Citadel of Doom.",0
//  ; 15
//                  dc.b    "% entered the Burning Waste.",0
//                  dc.b    "% found an oasis.",0
//                  dc.b    "% came to the hidden city of Azal.",0
//                  dc.b    "% discovered an outlying fort.",0
//                  dc.b    "% came to a small keep.",0
//  ; 20
//                  dc.b    "% came to an old castle.",0
//                  dc.b    "% came to a log cabin.",0
//                  dc.b    "% came to a dark stone tower.",0
//                  dc.b    "% came to an isolated cabin.",0
//                  dc.b    "% came to the Tombs of Hemsath.",0
//  ; 25
//                  dc.b    "% reached the Forbidden Keep.",0
//                  dc.b    "% found a cave in the hillside.",0

char place_msg[] =
    "\0"        // no message
    "\0"        // do not change
    "% returned to the village of Tambry.\0"
    "% came to Vermillion Manor.\0"
    "% reached the Mountains of Frost\0"
    // 5
    "% reached the Plain of Grief.\0"
    "% came to the city of Marheim.\0"
    "% came to the Witch's castle.\0"
    "% came to the Graveyard.\0"
    "% came to a great stone ring.\0"
    // 10
    "% came to a watchtower.\0"
    "% traveled to the great Bog.\0"
    "% came to the Crystal Palace.\0"
    "% came to mysterious Pixle Grove.\0"
    "% entered the Citadel of Doom.\0"
    // 15
    "% entered the Burning Waste.\0"
    "% found an oasis.\0"
    "% came to the hidden city of Azal.\0"
    "% discovered an outlying fort.\0"
    "% came to a small keep.\0"
    // 20
    "% came to an old castle.\0"
    "% came to a log cabin.\0"
    "% came to a dark stone tower.\0"
    "% came to an isolated cabin.\0"
    "% came to the Tombs of Hemsath.\0"
    // 25
    "% reached the Forbidden Keep.\0"
    "% found a cave in the hillside.\0"
    // "He entered the garden area.\0"        // of Mar's castle
    ;


//
//  _inside_msg
//                  dc.b    0        ; no message
//                  dc.b    0        ; do not change
//                  dc.b    "% came to a small chamber.",0
//                  dc.b    "% came to a large chamber.",0
//                  dc.b    "% came to a long passageway.",0
//  ; 5
//                  dc.b    "% came to a twisting tunnel.",0
//                  dc.b    "% came to a forked intersection.",0
//                  dc.b    "He entered the keep.",0    ; itemize
//                  dc.b    "He entered the castle.",0  ; itemize
//                  dc.b    "He entered the castle of King Mar.",0
//  ; 10
//                  dc.b    "He entered the sanctuary of the temple.",0
//                  dc.b    "% entered the Spirit Plane.",0
//                  dc.b    "% came to a large room.",0
//                  dc.b    "% came to an octagonal room.",0
//                  dc.b    "% traveled along a stone corridor.",0
//  ; 15
//                  dc.b    "% came to a stone maze.",0
//                  dc.b    "He entered a small building.",0
//                  dc.b    "He entered the building.",0
//                  dc.b    "He entered the tavern.",0
//                  dc.b    "He went inside the inn.",0
//  ; 20
//                  dc.b    "He entered the crypt.",0
//                  dc.b    "He walked into the cabin.",0
//                  dc.b    "He unlocked the door and entered.",0
//

char inside_msg[] =
    "\0"        // no message
    "\0"        // do not change
    "% came to a small chamber.\0"
    "% came to a large chamber.\0"
    "% came to a long passageway.\0"
    // 5
    "% came to a twisting tunnel.\0"
    "% came to a forked intersection.\0"
    "He entered the keep.\0"          // itemize
    "He entered the castle.\0"        // itemize
    "He entered the castle of King Mar.\0"
    // 10
    "He entered the sanctuary of the temple.\0"
    "% entered the Spirit Plane.\0"
    "% came to a large room.\0"
    "% came to an octagonal room.\0"
    "% traveled along a stone corridor.\0"
    // 15
    "% came to a stone maze.\0"
    "He entered a small building.\0"
    "He entered the building.\0"
    "He entered the tavern.\0"
    "He went inside the inn.\0"
    // 20
    "He entered the crypt.\0"
    "He walked into the cabin.\0"
    "He unlocked the door and entered.\0";

//
//  mst             dc.l    msg1-mst,msg2-mst,msg3-mst,msg4-mst,msg5-mst,msg6-mst
//                  dc.l    msg7-mst,msg7a-mst
//                  dc.l    msg8-mst,msg8a-mst,msg8b-mst
//                  dc.l    msg9-mst,msg9a-mst,msg9b-mst
//                  dc.l    msg10-mst,msg10a-mst,msg10b-mst
//                  dc.l    msg11-mst,msg11a-mst,msg12-mst
//
//  msg1            dc.b    XY,20/2,28,'   "Rescue the Talisman!"'
//                  dc.b    XY,20/2,39,"was the Mayor's plea."
//                  dc.b    XY,20/2,50,'"Only the Talisman can'
//                  dc.b    XY,20/2,61,'protect our village from'
//                  dc.b    XY,20/2,72,'the evil forces of the'
//                  dc.b    XY,20/2,83,'night." And so Julian'
//                  dc.b    XY,20/2,94,'set out on his quest to'
//                  dc.b    XY,20/2,105,'recover it.'
//                  dc.b    ETX
//
//  msg2            dc.b    XY,24/2,44,"Unfortunately for Julian,"
//                  dc.b    XY,24/2,55,"his luck had run out."
//                  dc.b    XY,24/2,66,"Many months passed and"
//                  dc.b    XY,24/2,77,"Julian did not return..."
//                  dc.b    ETX
//
//  msg3            dc.b    XY,40/2,44,"So Phillip set out,"
//                  dc.b    XY,40/2,55,"determined to find his"
//                  dc.b    XY,40/2,66,"brother and complete"
//                  dc.b    XY,40/2,77,"the quest."
//                  dc.b    ETX
//
//  msg4            dc.b    XY,24/2,44,"But sadly, Phillip's"
//                  dc.b    XY,24/2,55,"cleverness could not save"
//                  dc.b    XY,24/2,66,"him from the same fate"
//                  dc.b    XY,24/2,77,"as his older brother."
//                  dc.b    ETX
//
//  msg5            dc.b    XY,30/2,30,"So Kevin took up the"
//                  dc.b    XY,30/2,41,"quest, risking all, for"
//                  dc.b    XY,30/2,52,"the village had grown"
//                  dc.b    XY,30/2,63,"desperate. Young and"
//                  dc.b    XY,30/2,74,"inexperienced, his"
//                  dc.b    XY,30/2,85,"chances did not look"
//                  dc.b    XY,30/2,96,"good."
//                  dc.b    ETX
//  msg6
//                  dc.b    XY,20/2,31,"And so ends our sad tale."
//                  dc.b    XY,25/2,45,"The Lesson of the Story:"
//                  dc.b    XY,66/2,88,"Stay at Home!"
//                  dc.b    ETX
//  msg7
//                  dc.b    XY,28/2,32,"Having defeated the"
//                  dc.b    XY,28/2,43,"villainous Necromancer"
//                  dc.b    XY,28/2,54,"and recovered the"
//                  dc.b    XY,28/2,65,"Talisman, "
//                  dc.b    ETX
//  msg7a
//                  dc.b    XY,28/2,76,"returned to Marheim"    ; insert name here
//                  dc.b    XY,28/2,87,"where he wed the"
//                  dc.b    XY,28/2,98,"princess..."
//                  dc.b    ETX
//
//  msg8            dc.b    XY,21/2,26
//                  dc.b    ETX
//
//  msg8a           dc.b    " had rescued Katra,"
//                  dc.b    XY,21/2,37,"Princess of Marheim."
//                  dc.b    XY,21/2,48,"Though they had pledged"
//                  dc.b    XY,21/2,59,"their love for each, "
//                  dc.b    XY,21/2,70,"other, "
//                  dc.b    ETX
//
//  msg8b           dc.b    " knew that"
//                  dc.b    XY,21/2,81," his quest could not"
//                  dc.b    XY,21/2,92,"be forsaken."
//                  dc.b    ETX
//
//  msg9            dc.b    XY,21/2,33
//                  dc.b    ETX
//
//  msg9a           dc.b    " had rescued Karla"
//                  dc.b    XY,21/2,44,"(Katra's sister), Princess"
//                  dc.b    XY,21/2,55,"of Marheim. Though they"
//                  dc.b    XY,21/2,66,"had pledged their love"
//                  dc.b    XY,21/2,77,"for each other, ",ETX
//  msg9b           dc.b    XY,21/2,88,"knew that his quest"
//                  dc.b    XY,21/2,99,"could not be forsaken."
//                  dc.b    ETX
//
//  msg10           dc.b    XY,21/2,26
//                  dc.b    ETX
//
//  msg10a          dc.b    " had rescued Kandy"
//                  dc.b    XY,21/2,37,"(Katra's and Karla's"
//                  dc.b    XY,21/2,48,"sister), Princess of"
//                  dc.b    XY,21/2,59,"Marheim. Though they had"
//                  dc.b    XY,21/2,70,"pledged their love for"
//                  dc.b    XY,21/2,81,"each other, "
//                  dc.b    ETX

//  msg10b          dc.b    " knew "
//                  dc.b    XY,21/2,92,"that his quest could"
//                  dc.b    XY,21/2,103,"not be forsaken."
//                  dc.b    ETX
//
//  msg11           dc.b    XY,71/2,37,"After seeing the"
//                  dc.b    XY,35/2,48,"princess safely to her"
//                  dc.b    XY,35/2,59,"home city, and with a"
//                  dc.b    XY,35/2,70,"king's gift in gold,"
//                  dc.b    XY,35/2,81
//                  dc.b    ETX
//
//  msg11a          dc.b    " once more set"
//                  dc.b    XY,35/2,92,"out on his quest."
//                  dc.b    ETX
//
//  msg12           dc.b    XY,128/2,19,"So..."
//                  dc.b    XY,34/2,65,"You, game seeker, would guide the"
//                  dc.b    XY,10/2,75,"brothers to their destiny? You would"
//                  dc.b    XY,10/2,85,"aid them and give directions? Answer,"
//                  dc.b    XY,10/2,95,"then, these three questions and prove"
//                  dc.b    XY,10/2,105,"your fitness to be their advisor:"
//                  dc.b    ETX

UBYTE msg1[] =
    "\x80\x0a\x1c"        // XY,20/2,28
    "   \"Rescue the Talisman!\""
    "\x80\x0a\x27"        // XY,20/2,39
    "was the Mayor's plea."
    "\x80\x0a\x32"        // XY,20/2,50
    "\"Only the Talisman can"
    "\x80\x0a\x3d"        // XY,20/2,61
    "protect our village from"
    "\x80\x0a\x48"        // XY,20/2,72
    "the evil forces of the"
    "\x80\x0a\x53"        // XY,20/2,83
    "night.\" And so Julian"
    "\x80\x0a\x5e"        // XY,20/2,94
    "set out on his quest to"
    "\x80\x0a\x69"        // XY,20/2,105
    "recover it.";

UBYTE msg2[] =
    "\x80\x0c\x2c"        // XY,24/2,44
    "Unfortunately for Julian,"
    "\x80\x0c\x37"        // XY,24/2,55
    "his luck had run out."
    "\x80\x0c\x42"        // XY,24/2,66
    "Many months passed and"
    "\x80\x0c\x4d"        // XY,24/2,77
    "Julian did not return...";

UBYTE msg3[] =
    "\x80\x14\x2c"        // XY,40/2,44
    "So Phillip set out,"
    "\x80\x14\x37"        // XY,40/2,55
    "determined to find his"
    "\x80\x14\x42"        // XY,40/2,66
    "brother and complete"
    "\x80\x14\x4d"        // XY,40/2,77
    "the quest.";

UBYTE msg4[] =
    "\x80\x0c\x2c"        // XY,24/2,44
    "But sadly, Phillip's"
    "\x80\x0c\x37"        // XY,24/2,55
    "cleverness could not save"
    "\x80\x0c\x42"        // XY,24/2,66
    "him from the same fate"
    "\x80\x0c\x4d"        // XY,24/2,77
    "as his older brother.";

UBYTE msg5[] =
    "\x80\x0f\x1e"        // XY,30/2,30
    "So Kevin took up the"
    "\x80\x0f\x29"        // XY,30/2,41
    "quest, risking all, for"
    "\x80\x0f\x34"        // XY,30/2,52
    "the village had grown"
    "\x80\x0f\x3f"        // XY,30/2,63
    "desperate. Young and"
    "\x80\x0f\x4a"        // XY,30/2,74
    "inexperienced, his"
    "\x80\x0f\x55"        // XY,30/2,85
    "chances did not look"
    "\x80\x0f\x60"        // XY,30/2,96
    "good.";

UBYTE msg6[] =
    "\x80\x0a\x1f"        // XY,20/2,31
    "And so ends our sad tale."
    "\x80\x0c\x2d"        // XY,25/2,45
    "The Lesson of the Story:"
    "\x80\x21\x58"        // XY,66/2,88
    "Stay at Home!";

UBYTE msg7[] =
    "\x80\x0e\x20"        // XY,28/2,32
    "Having defeated the"
    "\x80\x0e\x2b"        // XY,28/2,43
    "villanous Necromancer"
    "\x80\x0e\x36"        // XY,28/2,54
    "and recovered the"
    "\x80\x0e\x41"        // XY,28/2,65
    "Talisman, ";

UBYTE msg7a[] =
    "\x80\x0e\x4c"        // XY,28/2,76 // insert name here
    "returned to Marheim"
    "\x80\x0e\x57"        // XY,28/2,87
    "where he wed the"
    "\x80\x0e\x62"        // XY,28/2,98
    "princess...";

UBYTE msg8[] = "\x80\x0a\x1a";        // XY,21/2,26

UBYTE msg8a[] =
    " had rescued Katra,"
    "\x80\x0a\x25"        // XY,21/2,37
    "Princess of Marheim."
    "\x80\x0a\x30"        // XY,21/2,48
    "Though they had pledged"
    "\x80\x0a\x3b"        // XY,21/2,59
    "their love for each, "
    "\x80\x0a\x46"        // XY,21/2,70
    "other, ";

UBYTE msg8b[] =
    " knew that"
    "\x80\x0a\x51"        // XY,21/2,81
    " his quest could not"
    "\x80\x0a\x5c"        // XY,21/2,92
    "be forsaken.";

UBYTE msg9[] = "\x80\x0a\x21";        // XY,21/2,33

UBYTE msg9a[] =
    " had rescued Karla"
    "\x80\x0a\x2c"        // XY,21/2,44
    "(Katra's sister), Princess"
    "\x80\x0a\x37"        // XY,21/2,55
    "of Marheim. Though they"
    "\x80\x0a\x42"        // XY,21/2,66
    "had pledged their love"
    "\x80\x0a\x4d"        // XY,21/2,77
    "for each other, ";

UBYTE msg9b[] =
    "\x80\x0a\x58"        // XY,21/2,88
    "knew that his quest"
    "\x80\x0a\x63"        // XY,21/2,99
    "could not be forsaken.";

UBYTE msg10[] = "\x80\x0a\x1a";        // XY,21/2,26

UBYTE msg10a[] =
    " had rescued Kandy"
    "\x80\x0a\x25"        // XY,21/2,37
    "(Katra's and Karla's"
    "\x80\x0a\x30"        // XY,21/2,48
    "sister), Princess of"
    "\x80\x0a\x3b"        // XY,21/2,59
    "Marheim. Though they had"
    "\x80\x0a\x46"        // XY,21/2,70
    "pledged their love for"
    "\x80\x0a\x51"        // XY,21/2,81
    "each other, ";

UBYTE msg10b[] =
    " knew "
    "\x80\x0a\x5c"        // XY,21/2,92
    "that his quest could"
    "\x80\x0a\x67"        // XY,21/2,103
    "not be forsaken.";

UBYTE msg11[] =
    "\x80\x23\x25"        // XY,71/2,37
    "After seeing the"
    "\x80\x11\x30"        // XY,35/2,48
    "princess safely to her"
    "\x80\x11\x3b"        // XY,35/2,59
    "home city, and with a"
    "\x80\x11\x46"        // XY,35/2,70
    "king's gift in gold,"
    "\x80\x11\x51";        // XY,35/2,81

UBYTE msg11a[] =
    " once more set"
    "\x80\x11\x5c"        // XY,35/2,92
    "out on his quest.";

UBYTE msg12[] =
    "\x80\x40\x13"        // XY,128/2,19
    "So..."
    "\x80\x11\x41"        // XY,34/2,65
    "You, game seeker, would guide the"
    "\x80\x05\x4b"        // XY,10/2,75
    "brothers to their destiny? You would"
    "\x80\x05\x55"        // XY,10/2,85
    "aid them and give directions? Answer,"
    "\x80\x05\x5f"        // XY,10/2,95
    "then, these three questions and prove"
    "\x80\x05\x69"        // XY,10/2,105
    "your fitness to be their advisor:";

UBYTE * mst[] = {msg1,  msg2, msg3,  msg4,  msg5,  msg6,   msg7,   msg7a, msg8,   msg8a,
                 msg8b, msg9, msg9a, msg9b, msg10, msg10a, msg10b, msg11, msg11a, msg12};

//                  cseg
//
//  XY              equ     128     ; then x/2 then y
//  ETX             equ     0
//
//                  public  _ssp,_placard_text
//
//  _placard_text
//                  move.l  4(sp),d0
//                  add.w   d0,d0
//                  add.w   d0,d0
//                  lea     mst,a0
//                  add.l   (a0,d0),a0
//                  move.l  a0,4(sp)
//                  jmp     _ssp

// placard_text - print Nth message on placard
void placard_text(int32_t n)
{
    RUNLOGF("<= placard_text(%d)", n);
    ssp(mst[n]);
}

//                  dseg
//                  public        _speeches
//
// _speeches
// ; 0 - ogre speech
//                 dc.b        '% attempted to communicate with the Ogre '
//                 dc.b        'but a guttural snarl was the only response.',0
// ; 1 - orc speech
//                 dc.b        '"Human must die!" said the goblin-man.',0
// ; 2 - wraith / 3 - skeleton speech
//                 dc.b        '"Doom!" wailed the wraith.',0
//                 dc.b        'A clattering of bones was the only reply.',0
// ; 4 - snake / 5 - salamander
//                 dc.b        '% knew that it is a waste of time to talk to a snake.',0
//                 dc.b        '...',0
// ; 6 - loraii / 7 - necromancer
//                 dc.b        'There was no reply.',0
//                 dc.b        '"Die, foolish mortal!" he said.',0
// ; 8 - messages
//                 dc.b        '"No need to shout, son!" he said.',0
// ; 9 - woodcutter message - note he is not a setfig
//                 dc.b        '"Nice weather we'
//                 dc.b        "'re having, isn'"
//                 dc.b        't it?" queried the ranger.',0
// ; 10 - woodcutter message 2
//                 dc.b        '"Good luck, sonny!" said the ranger. "Hope you win!"',0
// ; 11 - woodcutter message 3
//                 dc.b        '"If you need to cross the lake" said the ranger, '
//                 dc.b        '"There',"'",'s a raft just north of here."',0
// ; 12 - bartender message 1
//                 dc.b        '"Would you like to buy something?" said the tavern keeper. '
//                 dc.b        '"Or do you just need lodging for the night?"',0
// ; 13 - bartender message 2
//                 dc.b        '"Good Morning." said the tavern keeper. "Hope you slept well."',0
// ; 14 - bartender message 3
//                 dc.b        '"Have a drink!" said the tavern keeper."',0
// ; 15 - guard message
//                 dc.b        '"State your business!" said the guard.',13
//                 dc.b        '"My business is with the king." stated %, respectfully.',0
// ; 16 - princess message
//                 dc.b        '"Please, sir, rescue me from this horrible prison!" '
//                 dc.b        'pleaded the princess.',0
// ; 17 - king messages
//                 dc.b        '"I cannot help you, young man." said the king. '
//                 dc.b        '"My armies are decimated, and I fear that with the '
//                 dc.b        'loss of my children, I have lost all hope."',0
// ; 18 - king message 2
//                 dc.b        '"Here is a writ designating you as my '
//                 dc.b        'official agent. Be sure and show this '
//                 dc.b        'to the Priest before you leave Marheim.',0
// ; 19 - king message 3
//                 dc.b        '"I',"'",'m afraid I cannot help you, young man. I already '
//                 dc.b        'gave the golden statue to the other young man.',0
// ; 20 - noble message 1
//                 dc.b        '"If you could rescue the king',"'",'s daughter," said '
//                 dc.b        'Lord Trane, "The King',"'",'s courage would be restored."',0
// ; 21 - give bone to someone
//                 dc.b        '"Sorry, I have no use for it."',0
// ; 22 - ranger message
//                 dc.b        '"The dragon',"'",'s cave is directly north of here." said the ranger."',0
// ; 23 - beggar message 1 - if gives gold, increase kindness
//                 dc.b        '"Alms! Alms for the poor!"',0
// ; 24 - beggar message 2
//                 dc.b        '"I have a prophecy for you, m',"'",'lord." said the beggar. '
//                 dc.b        '"You must seek two women, one Good, one Evil."',0
// ; 25 - beggar message 3
//                 dc.b        '"Lovely Jewels, glint in the night - give to us the '
//                 dc.b        'gift of Sight!" he said.',0
// ; 26 - beggar message 4
//                 dc.b        '"Where is the hidden city? How can you find it when you '
//                 dc.b        'cannot even see it?" said the beggar.',0
// ; 27 - wizard message 1
//                 dc.b        '"Kind deeds could gain thee a friend from the sea."',0
// ; 28 - wizard message 2
//                 dc.b        '"Seek the place that is darker '
//                 dc.b        'than night - There you shall find '
//                 dc.b        'your goal in sight!" said the wizard, cryptically.',0
// ; 29 - wizard message 3
//                 dc.b        '"Like the eye itself, a crystal Orb can help to find things '
//                 dc.b        'concealed."',0
// ; 30 - wizard message 4
//                 dc.b        '"The Witch lives in the dim forest of Grimwood, where '
//                 dc.b        'the very trees are warped to her will. Her gaze is Death!"',0
// ; 31 - wizard message 5
//                 dc.b        '"Only the light of the Sun can destroy the Witch',"'",'s Evil."',0
// ; 32 - wizard message 6
//                 dc.b        '"The maiden you seek lies imprisoned in an unreachable '
//                 dc.b        'castle surrounded by unclimbable mountains."',0
// ; 33 - wizard message 7
//                 dc.b        "Tame the golden beast and no mountain may deny you! '
//                 dc.b        'But what rope could hold such a creature?"',0
// ; 34 - wizard message 8
//                 dc.b        '"Just what I needed!" he said.',0
// ; 35 - wizard message 9
//                 dc.b        '"Away with you, young ruffian!" said the Wizard. '
//                 dc.b        '"Perhaps you can find some small animal to torment '
//                 dc.b        'if that pleases you!"',0
// ; 36 - cleric message 1
//                 dc.b        "You must seek your enemy on the spirit plane. '
//                 dc.b        'It is hazardous in the extreme. Space may twist, '
//                 dc.b        'and time itself may run backwards!"',0
// ; 37 - cleric message 2
//                 dc.b        '"When you wish to travel quickly, seek the power of the '
//                 dc.b        'Stones." he said.',0
// ; 38 - cleric message 3
//                 dc.b        '"Since you are brave of heart, I shall Heal all your wounds."',13
//                 dc.b        'Instantly % felt much better.',0
// ; 39 - cleric message 4
//                 dc.b        '"Ah! You have a writ from the king. Here is '
//                 dc.b        'one of the golden statues of Azal-Car-Ithil. '
//                 dc.b        'Find all five and you',"'",'ll find the vanishing city."',0
// ; 40 - cleric message 5
//                 dc.b        '"Repent, Sinner! Thou art an uncouth brute and I have no '
//                 dc.b        'interest in your conversation!"',0
// ; 41 - dreamknight message 1
//                 dc.b        '"Ho there, young traveler!" said the black figure. '
//                 dc.b        '"None may enter the sacred shrine of the People '
//                 dc.b        'who came Before!"',0
// ; 42 - dream knight message 2
//                 dc.b        '"Your prowess in battle is great." said the Knight '
//                 dc.b        'of Dreams. "You have earned the right to enter and '
//                 dc.b        'claim the prize."',0
// ; 43 - necromancer message 1
//                 dc.b        '"So this is the so-called Hero who has been sent to '
//                 dc.b        'hinder my plans. Simply Pathetic. Well, try this, '
//                 dc.b        'young Fool!"',0
// ; 44 - necromancer message 2
//                 dc.b        '% gasped. The Necromancer had been transformed into '
//                 dc.b        'a normal man. All of his evil was gone.',0
// ; 45 - sorceress message
//                 dc.b        '"%." said the Sorceress. "Welcome. Here is one of the '
//                 dc.b        'five golden figurines you will need."',13
//                 dc.b        '"Thank you." said %.',0
// ; 46 - witch message
//                 dc.b        '"Look into my eyes and Die!!" hissed the witch.',13
//                 dc.b        '"Not a chance!" replied %',0
// ; 47 - spectre message
//                 dc.b        'The Spectre spoke. "HE has usurped my place '
//                 dc.b        'as lord of undead. Bring me bones of the ancient '
//                 dc.b        'King and I',"'",'ll help you destroy him."',0
// ; 48 - spectre
//                 dc.b        '% gave him the ancient bones.',13
//                 dc.b        '"Good! That spirit now rests quietly in my halls. Take '
//                 dc.b        'this crystal shard."',0
// ; 49 - ghost message 1
//                 dc.b        '"%..." said the apparition. "I am the ghost of your '
//                 dc.b        'dead brother. Find my bones -- there you will find some '
//                 dc.b        'things you need.',0
// ; 50 - if we give gold to anyone
//                 dc.b        '% gave him some gold coins. ',13
//                 dc.b        '"Why, thank you, young sir!"',0
// ; 51 - if we try to buy from a non-buyer
//                 dc.b        '"Sorry, but I have nothing to sell."',0
// ; 52 - if we try to buy from no-one
//                 dc.b        0
// ; 53-55 - more ranger messages
//                 dc.b        '"The dragon',"'",'s cave is east of here." said the ranger."',0
//                 dc.b        '"The dragon',"'",'s cave is west of here." said the ranger."',0
//                 dc.b        '"The dragon',"'",'s cave is south of here." said the ranger."',0
// ; 56 - turtle message 1
//                 dc.b        '"Oh, thank you for saving my eggs, kind man!" said the turtle. '
//                 dc.b        '"Take this seashell as a token of my gratitude."',0
// ; 57 - turtle message 2
//                 dc.b        '"Just hop on my back if you need a ride somewhere." said the turtle.',0
// ; 58 - witch/necro
//                 dc.b        '"Stupid fool, you can',"'",'t hurt me with that!"',0
// ; 59 - necro defy
//                 dc.b        '"Your magic won',"'",'t work here, fool!"',0
// ; 60 - witch powerless
//                 dc.b        'The Sunstone has made the witch vulnerable!',0
//                 end
//

char speeches[] =
    // 0 - ogre speech
    "% attempted to communicate with the Ogre "
    "but a guttural snarl was the only response.\0"
    // 1 - orc speech
    "\"Human must die!\" said the goblin-man.\0"
    // 2 - wraith / 3 - skeleton speech
    "\"Doom!\" wailed the wraith.\0"
    "A clattering of bones was the only reply.\0"
    // 4 - snake / 5 - salamander
    "% knew that it is a waste of time to talk to a snake.\0"
    "...\0"
    // 6 - loraii / 7 - necromancer
    "There was no reply.\0"
    "\"Die, foolish mortal!\" he said.\0"
    // 8 - messages
    "\"No need to shout, son!\" he said.\0"
    // 9 - woodcutter message - note he is not a setfig
    "\"Nice weather we're having, isn't it?\" queried the ranger.\0"
    // 10 - woodcutter message 2
    "\"Good luck, sonny!\" said the ranger. \"Hope you win!\"\0"
    // 11 - woodcutter message 3
    "\"If you need to cross the lake\" said the ranger, "
    "\"There's a raft just north of here.\"\0"
    // 12 - bartender message 1
    "\"Would you like to buy something?\" said the tavern keeper. "
    "\"Or do you just need lodging for the night?\"\0"
    // 13 - bartender message 2
    "\"Good Morning.\" said the tavern keeper. \"Hope you slept well.\"\0"
    // 14 - bartender message 3
    "\"Have a drink!\" said the tavern keeper.\0"
    // 15 - guard message
    "\"State your business!\" said the guard.\r"
    "\"My business is with the king.\" stated %, respectfully.\0"
    // 16 - princess message
    "\"Please, sir, rescue me from this horrible prison!\" "
    "pleaded the princess.\0"
    // 17 - king messages
    "\"I cannot help you, young man.\" said the king. "
    "\"My armies are decimated, and I fear that with the "
    "loss of my children, I have lost all hope.\"\0"
    // 18 - king message 2
    "\"Here is a writ designating you as my "
    "official agent. Be sure and show this "
    "to the Priest before you leave Marheim.\"\0"
    // 19 - king message 3
    "\"I'm afraid I cannot help you, young man. I already "
    "gave the golden statue to the other young man.\"\0"
    // 20 - noble message 1
    "\"If you could rescue the king's daughter,\" said "
    "Lord Trane, \"The King's courage would be restored.\"\0"
    // 21 - give bone to someone
    "\"Sorry, I have no use for it.\"\0"
    // 22 - ranger message
    "\"The dragon's cave is directly north of here.\" said the ranger.\0"
    // 23 - beggar message 1 - if gives gold, increase kindness
    "\"Alms! Alms for the poor!\"\0"
    // 24 - beggar message 2
    "\"I have a prophecy for you, m'lord.\" said the beggar. "
    "\"You must seek two women, one Good, one Evil.\"\0"
    // 25 - beggar message 3
    "\"Lovely Jewels, glint in the night - give to us the "
    "gift of Sight!\" he said.\0"
    // 26 - beggar message 4
    "\"Where is the hidden city? How can you find it when you "
    "cannot even see it?\" said the beggar.\0"
    // 27 - wizard message 1
    "\"Kind deeds could gain thee a friend from the sea.\"\0"
    // 28 - wizard message 2
    "\"Seek the place that is darker "
    "than night - There you shall find "
    "your goal in sight!\" said the wizard, cryptically.\0"
    // 29 - wizard message 3
    "\"Like the eye itself, a crystal Orb can help to find things "
    "concealed.\"\0"
    // 30 - wizard message 4
    "\"The Witch lives in the dim forest of Grimwood, where "
    "the very trees are warped to her will. Her gaze is Death!\"\0"
    // 31 - wizard message 5
    "\"Only the light of the Sun can destroy the Witch's Evil.\"\0"
    // 32 - wizard message 6
    "\"The maiden you seek lies imprisoned in an unreachable "
    "castle surrounded by unclimbable mountains.\"\0"
    // 33 - wizard message 7
    "Tame the golden beast and no mountain may deny you! "
    "But what rope could hold such a creature?\"\0"
    // 34 - wizard message 8
    "\"Just what I needed!\" he said.\0"
    // 35 - wizard message 9
    "\"Away with you, young ruffian!\" said the Wizard. "
    "\"Perhaps you can find some small animal to torment "
    "if that pleases you!\"\0"
    // 36 - cleric message 1
    "You must seek your enemy on the spirit plane. "
    "It is hazardous in the extreme. Space may twist, "
    "and time itself may run backwards!\"\0"
    // 37 - cleric message 2
    "\"When you wish to travel quickly, seek the power of the "
    "Stones.\" he said.\0"
    // 38 - cleric message 3
    "\"Since you are brave of heart, I shall Heal all your wounds.\"\r"
    "Instantly % felt much better.\0"
    // 39 - cleric message 4
    "\"Ah! You have a writ from the king. Here is "
    "one of the golden statues of Azal-Car-Ithil. "
    "Find all five and you'll find the vanishing city.\"\0"
    // 40 - cleric message 5
    "\"Repent, Sinner! Thou art an uncouth brute and I have no "
    "interest in your conversation!\"\0"
    // 41 - dreamknight message 1
    "\"Ho there, young traveler!\" said the black figure. "
    "\"None may enter the sacred shrine of the People "
    "who came Before!\"\0"
    // 42 - dream knight message 2
    "\"Your prowess in battle is great.\" said the Knight "
    "of Dreams. \"You have earned the right to enter and "
    "claim the prize.\"\0"
    // 43 - necromancer message 1
    "\"So this is the so-called Hero who has been sent to "
    "hinder my plans. Simply Pathetic. Well, try this, "
    "young Fool!\"\0"
    // 44 - necromancer message 2
    "% gasped. The Necromancer had been transformed into "
    "a normal man. All of his evil was gone.\0"
    // 45 - sorceress message
    "\"%.\" said the Sorceress. \"Welcome. Here is one of the "
    "five golden figurines you will need.\"\r"
    "\"Thank you.\" said %.\0"
    // 46 - witch message
    "\"Look into my eyes and Die!!\" hissed the witch.\r"
    "\"Not a chance!\" replied %\0"
    // 47 - spectre message
    "The Spectre spoke. \"HE has usurped my place "
    "as lord of undead. Bring me bones of the ancient "
    "King and I'll help you destroy him.\"\0"
    // 48 - spectre
    "% gave him the ancient bones.\r"
    "\"Good! That spirit now rests quietly in my halls. Take "
    "this crystal shard.\"\0"
    // 49 - ghost message 1
    "\"%...\" said the apparition. \"I am the ghost of your "
    "dead brother. Find my bones -- there you will find some "
    "things you need.\0"
    // 50 - if we give gold to anyone
    "% gave him some gold coins. \r"
    "\"Why, thank you, young sir!\"\0"
    // 51 - if we try to buy from a non-buyer
    "\"Sorry, but I have nothing to sell.\"\0"
    // 52 - if we try to buy from no-one
    "\0"
    // 53-55 - more ranger messages
    "\"The dragon's cave is east of here.\" said the ranger.\0"
    "\"The dragon's cave is west of here.\" said the ranger.\0"
    "\"The dragon's cave is south of here.\" said the ranger.\0"
    // 56 - turtle message 1
    "\"Oh, thank you for saving my eggs, kind man!\" said the turtle. "
    "\"Take this seashell as a token of my gratitude.\"\0"
    // 57 - turtle message 2
    "\"Just hop on my back if you need a ride somewhere.\" said the turtle.\0"
    // 58 - witch/necro
    "\"Stupid fool, you can't hurt me with that!\"\0"
    // 59 - necro defy
    "\"Your magic won't work here, fool!\"\0"
    // 60 - witch powerless
    "The Sunstone has made the witch vulnerable!\0";
