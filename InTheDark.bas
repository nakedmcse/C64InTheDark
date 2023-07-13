1 rem in the dark
2 rem objects
3 dim p(5):rem player x,y,dx,dy,room
4 dim m(10,5):rem monster x,y,dx,dy,room
5 dim rm(10,7):rem room x1,y1,x2,y2,disc,show,changed
6 for i=1 to 10:rm(i,1)=-1:next i:rem init rooms (-1 undefined)
7 dim ol(9):rem overlap check sx1,sy1,sx2,sy2,dx1,dy1,dx2,dy2,overlaped?
8 dim hd(3):rem hit detect x,y,hit? 
9 dim do(40,5):rem door x,y,r1 index,r2 index,opened
10 for i=1 to 40:do(i,1)=-1:next i:rem init doors (-1 undefined)
11 dim it(50,10):rem item x,y,room,type,taken,light,treas,d1idx,d2idx,redraw
12 for i=1 to 50:it(i,1)=-1:next i:rem init items (-1 undefined)
13 ri=0:di=0:ii=0:mi=0:rem room index, door index, item index, monster idx
14 sw=40:sh=25:rem c64 screen wxh
15 lw=6:lh=6:uw=10:uh=10:mw=3:mh=3:rem room sizes
16 dim rr(5):rem random range min1,min2,max1,max2,result
17 n$="":ni=0:a$="":ai=0:rem noun, adjective
18 dc=1:im=1:pd=0:mr=0:rem dungeon level, items max, player dir, move redraw 
19 l=0:t=0:li=0:xi=0:rem light, treasure, light item index, treas item index
20 mm=0:rx=0:dm=0:rem monsters max, rooms max, doors max
21 z=rnd(-ti):rem init random

100 rem main loop
101 gosub 900: rem set screen colors
102 gosub 2100: rem generate dungeon
103 print "generated";ri;"rooms":rx=ri
104 print "generated";di;"doors":dm=di
105 gosub 2700: rem generate items
106 print "generated";ii;"items"
107 gosub 2800: rem generate player
108 print "spawned player room";p(5);"at";p(1);p(2)
109 gosub 3000: rem generate monsters
110 print "spawned";mm;"monsters"
111 print chr$(147):rem cls
112 gosub 4200: rem draw frame
113 gosub 4100: rem draw dungeon
114 gosub 4300: rem draw player
115 gosub 4000: rem draw monsters
116 gosub 4400: rem show status
117 goto 116: rem loop to hold screen

900 rem set screen colors -- c64 specific!
901 poke 53280,0:rem border black
902 poke 53281,0:rem background black
903 poke 646,5:rem text green
904 print chr$(147):rem cls
905 return

910 rem move cursor -- c64 specific!
911 if hd(1)<0 then hd(1)=0
912 if hd(1)>sw-1 then hd(1)=sw-1
913 if hd(2)<0 then hd(2)=0
914 if hd(2)>sh-1 then hd(2)=sh-1
915 poke 781,hd(2):poke 782,hd(1):poke 783,0:rem set y,x,clear
916 sys 65520:rem kernal call to move cursor
917 return

1000 rem noun set
1001 if ni=0 then n$="match":return
1002 if ni=1 then n$="candle":return
1003 if ni=2 then n$="glow worms":return
1004 if ni=3 then n$="branch":return
1005 if ni=4 then n$="squash":return
1006 if ni=5 then n$="bulb":return
1007 if ni=6 then n$="torch":return
1008 if ni=7 then n$="rock":return
1009 if ni=8 then n$="torch":return
1010 if ni=9 then n$="brass lantern":return
1011 if ni=10 then n$="painting":return
1012 if ni=11 then n$="egg":return
1013 if ni=12 then n$="jewel":return
1014 if ni=13 then n$="belt buckle":return
1015 if ni=14 then n$="casket":return
1016 if ni=15 then n$="crystal skull":return
1017 if ni=16 then n$="pearl":return
1018 if ni=17 then n$="piece of eight":return
1019 if ni=18 then n$="fish scale":return
1020 if ni=19 then n$="carpenters chalice":return
1021 return

1100 rem adjective set
1101 if ai=0 then a$="glimmering":return
1102 if ai=1 then a$="shimmering":return
1103 if ai=2 then a$="bright":return
1104 if ai=3 then a$="golden":return
1105 if ai=4 then a$="sparkling":return
1106 if ai=5 then a$="battery powered":return
1107 if ai=6 then a$="radiant":return
1108 if ai=7 then a$="luminos":return
1109 if ai=8 then a$="flashing":return
1110 if ai=9 then a$="brilliant":return
1111 if ai=10 then a$="wooden":return
1112 if ai=11 then a$="illustrated":return
1113 if ai=12 then a$="golden":return
1114 if ai=13 then a$="bejeweled":return
1115 if ai=14 then a$="plain":return
1116 if ai=15 then a$="resplendant":return
1117 if ai=16 then a$="ghostly":return
1118 if ai=17 then a$="oozing":return
1119 if ai=18 then a$="gigantic":return
1120 if ai=19 then a$="clockwork":return
1121 return

1199 rem room.inc related code
1200 rem firstroom - gen first room
1201 rm(1,1)=int(rnd(1)*(sw-uw-1))+1:rem x1
1202 rm(1,2)=int(rnd(1)*(sh-uh-1))+1:rem y1
1203 rw=int(rnd(1)*(uw-lw))+lw+1
1204 rh=int(rnd(1)*(uh-lh))+lh+1
1205 rm(1,3)=rm(1,1)+rw:rem x2
1206 rm(1,4)=rm(1,2)+rh:rem y2
1207 rm(1,5)=0:rm(1,6)=1:rm(1,7)=0:rem disc/show/changed
1208 return

1300 rem overlap - do rooms overlap
1301 if ol(1)<ol(7) and ol(3)>ol(5) and ol(2)<ol(8) and ol(4)>ol(6) goto 1303
1302 ol(9)=0:return:rem no overlap
1303 ol(9)=1:return:rem overlap

1400 rem hitwall
1401 for i=1 to 10:if rm(i,1)=-1 goto 1405
1402 xd=hd(1)-rm(i,1):xe=hd(1)-rm(i,3)
1403 yd=hd(2)-rm(i,2):ye=hd(2)-rm(i,4)
1404 if xd>=0 and xe<=0 and (yd=0 or ye=0) hd(3)=1:return:rem y-hit
1404 if yd>=0 and ye<=0 and (xd=0 or xe=0) hd(3)=1:return:rem x-hit
1405 next i
1406 hd(3)=0:return:rem no hit wall

1500 rem hitdoor
1501 for i=1 to 40:if do(i,1)=-1 goto 1503
1502 if do(i,1)=hd(1) and do(i,2)=hd(2) then hd(3)=i:return:rem door hit
1503 next i
1504 hd(3)=0:return:rem no hit door

1600 rem hitroom
1601 for i=1 to 10:if rm(i,1)=-1 goto 1605
1602 xd=hd(1)-rm(i,1):xe=hd(1)-rm(i,3)
1603 yd=hd(2)-rm(i,2):ye=hd(2)-rm(i,4)
1604 if xd>0 and xe<0 and yd>0 and ye<0 then hd(3)=i:return:rem room hit
1605 next i
1606 hd(3)=0:return:rem no room hit

1700 rem cansee - hd(1) = room index hd(2) = room target
1701 for cs = 1 to 40:if do(cs,1)=-1 goto 1704
1702 if hd(1)=do(cs,3) and hd(2)=do(cs,4) and do(cs,5)=1 goto 1706
1703 if hd(1)=do(cs,4) and hd(2)=do(cs,3) and do(cs,5)=1 goto 1706
1704 next cs
1705 hd(3)=0:return:rem cannot see
1706 hd(3)=1:return:rem can see

1800 rem nextroom - generate next room hd(3) 0 on fail
1801 d=int(rnd(1)*4):rem direction
1802 ds=d: rem starting direction
1803 ta=1: rem try again set true
1804 gn=1: rem generate next
1805 w=int(rnd(1)*(uw-lw))+lw+1
1806 h=int(rnd(1)*(uh-lh))+lh+1
1807 if d=0 then gosub 1900 : rem move right
1808 if d=1 then gosub 1920 : rem move left
1809 if d=2 then gosub 1940 : rem move up
1810 if d=3 then gosub 1960 : rem move down 
1811 for o=1 to ri:rem check for overlap
1812 ol(1)=rm(o,1):ol(2)=rm(o,2):ol(3)=rm(o,3):ol(4)=rm(o,4)
1813 ol(5)=rm(ri+1,1):ol(6)=rm(ri+1,2):ol(7)=rm(ri+1,3):ol(8)=rm(ri+1,4)
1814 ol(9)=0:gosub 1300: rem check overlap
1815 if ol(9)=1 then gosub 1980: rem fix overlap
1816 next o
1817 if gn=1 then ta=0:goto 1821: rem sucess, so no try again
1818 d = (d+1) - int((d+1)/4) * 4: rem d+1 mod 4
1819 if d=ds then ta=0: rem tried all ordinals
1820 if ta=1 goto 1805 : rem try again if set
1821 if gn=1 then ri = ri+1:hd(3)=1:goto 1823:rem inc room index on sucess
1822 if gn=0 then rm(ri+1,1)=-1:hd(3)=0: rem reset to undefined on fail
1823 return

1900 rem genrightroom
1901 rm(ri+1,3)=rm(ri,1):rem x2=crx1
1902 if rm(ri+1,3)-w < 1 then w = rm(ri+1,3)-1
1903 if w<mw then gn=0
1904 rm(ri+1,1)=rm(ri+1,3)-w: rem x1 = x2-w
1905 y=int(rnd(1)*(rm(ri,4)-rm(ri,2)-1))+rm(ri,2)+1:rem cry2-cry1-1
1906 if y-int(h/2) < 1 then h=y
1907 if y-int(h/2)+h >= sh then h=sh-y-1
1908 if h<mh then gn=0
1909 rm(ri+1,2)=y-int(h/2): rem y1
1910 rm(ri+1,4)=rm(ri+1,2)+h: rem y2
1911 return

1920 rem genleftroom
1921 rm(ri+1,1)=rm(ri,3):rem x1=crx2
1922 if rm(ri+1,1)+w > sw then w = sw-rm(ri+1,1)
1923 if w<mw then gn=0
1924 rm(ri+1,3)=rm(ri+1,1)+w: rem x2 = x1+w
1925 y=int(rnd(1)*(rm(ri,4)-rm(ri,2)-1))+rm(ri,2)+1:rem cry2-cry1-1
1926 if y-int(h/2) < 1 then h=y
1927 if y-int(h/2)+h >= sh then h=sh-y-1
1928 if h<mh then gn=0
1929 rm(ri+1,2)=y-int(h/2): rem y1
1930 rm(ri+1,4)=rm(ri+1,2)+h: rem y2
1931 return

1940 rem genuproom
1941 rm(ri+1,4)=rm(ri,2):rem y2=cry1
1942 if rm(ri+1,4)-h < 1 then h = rm(ri+1,4)-1
1943 if h<mh then gn=0
1944 rm(ri+1,2)=rm(ri+1,4)-h: rem y1 = y2-h
1945 x=int(rnd(1)*(rm(ri,3)-rm(ri,1)-1))+rm(ri,1)+1:rem crx2-crx1-1
1946 if x-int(w/2) < 1 then w=x
1947 if x-int(w/2)+w >= sw then w=sw-x-1
1948 if w<mw then gn=0
1949 rm(ri+1,1)=x-int(w/2): rem x1
1940 rm(ri+1,3)=rm(ri+1,1)+w: rem x2
1941 return

1960 rem gendownroom
1961 rm(ri+1,2)=rm(ri,4):rem y1=cry2
1962 if rm(ri+1,2)+h > sh then h = sh-rm(ri+1,2)
1963 if h<mh then gn=0
1964 rm(ri+1,4)=rm(ri+1,2)+h: rem y2 = y1+h
1965 x=int(rnd(1)*(rm(ri,3)-rm(ri,1)-1))+rm(ri,1)+1:rem crx2-crx1-1
1966 if x-int(w/2) < 1 then w=x
1967 if x-int(w/2)+w >= sw then w=sw-x-1
1968 if w<mw then gn=0
1969 rm(ri+1,1)=x-int(w/2): rem x1
1970 rm(ri+1,3)=rm(ri+1,1)+w: rem x2
1971 return

1980 rem fixoverlap
1981 if rm(ri+1,4)>rm(ri,2) then rm(ri+1,4)=rm(ri,2):goto 1985
1982 if rm(ri+1,2)<rm(ri,4) then rm(ri+1,2)=rm(ri,4):goto 1985
1983 if rm(ri+1,3)>rm(ri,1) then rm(ri+3,1)=rm(ri,1):goto 1985
1984 if rm(ri+1,1)<rm(ri,3) then rm(ri+1,1)=rm(ri,3)
1985 rw = rm(ri+1,3)-rm(ri+1,1):rh = rm(ri+1,4)-rm(ri+1,2)
1986 if rw<mw or rh<mh then gn=0: rem overlap cannot be fixed by clip
1987 return

2000 rem doornotfound - hd(1) = room index hd(2) = room target
2001 fd = 0
2002 for k = 1 to 40:if do(k,1)=-1 goto 2005
2003 if hd(1)=do(k,3) and hd(2)=do(k,4) then fd=1 : goto 2006
2004 if hd(1)=do(k,4) and hd(2)=do(k,3) then fd=1 : goto 2006
2005 next k
2006 if fd=0 then hd(3)=1:return:rem door not found
2007 if fd=1 then hd(3)=0:return:rem door found

2020 rem randominrange - rr min1,min2,max1,max2,result
2021 if rr(1)>rr(2) then am=rr(1)+1:goto 2023
2022 am=rr(2)+1
2023 if rr(3)<rr(4) then ax=rr(3)-1:goto 2025
2024 ax=rr(4)-1
2025 ar=ax-am
2026 if a>0 then rr(5)=am+int(rnd(1)*a):return
2027 rr(5)=am:return

2040 rem generatedoors
2041 di = 1
2042 for i = 1 to ri : rem compare room to all prev rooms
2043 for j = 1 to i 
2044 do(di,3)=i:do(di,4)=j:do(di,5)=0: rem r1,r2,closed
2045 hd(1)=i:hd(2)=j:hd(3)=0:gosub 2000: rem check no existing door
2046 if hd(3)=0 goto 2051
2047 if rm(i,3)=rm(j,1) and rm(j,2)<rm(i,4) and rm(j,4)>rm(i,2) then gosub 2060
2048 if rm(i,1)=rm(j,3) and rm(j,2)<rm(i,4) and rm(j,4)>rm(i,2) then gosub 2070
2049 if rm(i,4)=rm(j,2) and rm(j,1)<rm(i,3) and rm(j,3)>rm(i,1) then gosub 2080
2050 if rm(i,2)=rm(j,4) and rm(j,1)<rm(i,3) and rm(j,3)>rm(i,1) then gosub 2090
2051 next j
2052 next i
2053 di = di-1: rem di is next door working on
2054 return

2060 rem eastdoor
2061 do(di,1)=rm(i,3)
2062 rr(1)=rm(i,2):rr(2)=rm(j,2):rr(3)=rm(i,4):rr(4)=rm(j,4):gosub 2020
2063 do(di,2)=rr(5)
2064 di=di+1 : return

2070 rem westdoor
2061 do(di,1)=rm(i,1)
2062 rr(1)=rm(i,2):rr(2)=rm(j,2):rr(3)=rm(i,4):rr(4)=rm(j,4):gosub 2020
2063 do(di,2)=rr(5)
2064 di=di+1 : return

2080 rem northdoor
2061 do(di,2)=rm(i,4)
2062 rr(1)=rm(i,1):rr(2)=rm(j,1):rr(3)=rm(i,3):rr(4)=rm(j,3):gosub 2020
2063 do(di,1)=rr(5)
2064 di=di+1 : return

2090 rem southdoor
2091 do(di,2)=rm(i,2)
2092 rr(1)=rm(i,1):rr(2)=rm(j,1):rr(3)=rm(i,3):rr(4)=rm(j,3):gosub 2020
2093 do(di,1)=rr(5)
2094 di=di+1 : return

2100 rem generatedungeon
2101 at=0
2102 print chr$(147)
2103 ri=1:hd(3)=1:at=at+1:print "generating dungeon attempt";at;"..."
2104 gosub 1200: rem create first room
2105 for r=2 to 9
2107 if hd(3)=1 then gosub 1800: rem create next room
2108 next r
2109 if ri<5 goto 2102:rem less than 5 rooms, retry
2110 gosub 2040: rem generate doors
2111 return

2199 rem items.inc related code
2200 rem generatelight
2201 p = rnd(1)
2202 dl=1:du=3:rem base values
2203 if p>0.95 then dl=9:du=10:goto 2207
2204 if p>0.9 then dl=7:du=9:goto 2207
2205 if p>0.8 then dl=4:du=8:goto 2207
2206 if p>0.6 then dl=2:du=5
2207 mu=1:rem base multiplier - worst 1:1
2208 if dc+1<=16 then mu = int(16/dc+1):rem light gets worse with level
2209 it(ii,4)=1:rem type light 1
2210 it(ii,5)=0:rem taken false
2211 it(ii,6)=(int(rnd(1)*(du-dl))+dl)*mu:rem light level
2212 it(ii,7)=0:rem treasure value
2213 it(ii,8)=(int(rnd(1)*(du-dl))+dl): rem d1
2214 it(ii,9)=int(rnd(1)*10): rem d2
2215 it(ii,10)=0:rem redraw
2216 return

2300 rem generatetreasure
2301 it(ii,4)=2:rem type treasure 2
2302 it(ii,5)=0:rem taken false
2303 it(ii,6)=0:rem light level
2304 it(ii,7)=1:rem treasure value (1 - all equal)
2305 it(ii,8)=int(rnd(1)*10)+10: rem d1
2306 it(ii,9)=int(rnd(1)*10)+10: rem d2
2307 it(ii,10)=0:rem redraw
2308 return

2400 rem hititem
2401 hd(3)=-1:rem no hit
2402 z=1
2403 if it(z,1)=hd(1) and it(z,2)=hd(2) and it(z,5)=0 then hd(3)=z
2405 z=z+1
2406 if hd(3)=-1 and z<=im goto 2403:rem repeat until all checked
2407 return

2500 rem setallredraw
2501 for z=1 to im:it(z,10)=1:next z
2502 return

2600 rem takeitem
2601 it(ii,5)=1:it(ii,10)=1:rem set taken and redraw
2602 if it(ii,6)>0 then l=it(ii,6):li=ii:gosub 2500:rem light
2603 if it(ii,7)>0 then t=t+it(ii,7):xi=ii:ct=3:rem treas -- todo ct
2604 return

2700 rem generate items - 0-3 per room
2701 ii=1:im=1:gosub 2200:rem generate first light
2702 for i=1 to ri
2703 for j=1 to 4
2704 q = rnd(1):hd(3)=-1
2705 if q<=0.4 goto 2715:rem no item if <0.4
2706 it(ii+1,10)=1:rem set redraw
2707 it(ii+1,1)=int(rnd(1)*(rm(i,3)-rm(i,1)-2))+rm(i,1)+1:rem gen x in room
2708 it(ii+1,2)=int(rnd(1)*(rm(i,4)-rm(i,2)-2))+rm(i,2)+1:rem gen y in room
2709 it(ii+1,3)=i:rem room
2710 hd(1)=it(ii+1,1):hd(2)=it(ii+1,2):gosub 2400:rem chk if other items hit
2711 if hd(3)<>-1 goto 2704:rem repeat if hit
2712 ii=ii+1:im=im+1:rem inc index and max count
2713 if q>0.8 then gosub 2300:goto 2715:rem p>0.8 gen treasure
2714 gosub 2200:rem else gen light
2715 next j
2716 next i
2717 return

2799 rem player.inc related code
2800 rem generateplayer - spawn in random room
2801 w = int(rnd(1)*ri)+1
2802 hd(1)=int(rnd(1)*(rm(w,3)-rm(w,1)-2))+rm(w,1)+1:rem spawn x
2803 hd(2)=int(rnd(1)*(rm(w,4)-rm(w,2)-2))+rm(w,2)+1:rem spawn y
2804 gosub 2400:rem check not spawn on item
2805 if hd(3)<>-1 goto 2802:rem try again on hit
2806 p(1)=hd(1):p(2)=hd(2):p(3)=p(1):p(4)=p(2):p(5)=w:rem set x,y,room 
2807 rm(w,5)=1:ii=1:gosub 2600:rem disc room,take first item
2808 return

2900 rem moveplayer
2901 mr=0:hd(1)=p(1):hd(2)=p(2):rem set redraw,x,y
2902 if pd<0 or pd>3 then return:rem handle invalid direction
2903 if pd=0 then hd(1)=p(1)-1:goto 2907:rem left
2904 if pd=1 then hd(1)=p(1)+1:goto 2907:rem right
2905 if pd=2 then hd(2)=p(2)-1:goto 2907:rem up
2906 if pd=3 then hd(2)=p(2)+1:rem down
2907 gosub 1500:rem check for hit door
2908 if hd(3)=-1 goto 2911: rem not hit door
2909 do(hd(3),5)=1:mr=1:rem opened door,set redraw
2910 rm(do(hd(3),3),5)=1:rm(do(hd(3),4),5)=1:rem set rooms discovered
2911 gosub 1400:rem check wall hit
2912 if hd(3)=1 then return:rem wall hit do nothing
2913 p(1)=hd(1):p(2)=hd(2):rem actually move player
2914 z=p(5):hd(3)=-1:rem get room number, set no change to room
2914 if (hd(1)>rm(z,1) or hd(1)<rm(z,3)) then gosub 1600:goto 2916
2915 if (hd(2)>rm(z,2) or hd(2)<rm(z,4)) then gosub 1600:rem check room bound
2916 if hd(3)=-1 goto 2918:rem couldnt find room/no change
2917 p(5)=hd(3):mr=1:rem set new room, redraw
2918 gosub 2400:rem check for item hit
2919 if hd(3)=-1 goto x:rem no item hit
2920 ii=hd(3):gosub 2600:mr=1:rem take item on hit, set redraw
2921 if l>0 then l=l-1:rem decrement light
2922 if l=0 then mr=1:gosub 2500:rem light out - hide all
2933 gosub 3300:rem move monsters
2934 return

2999 rem monster.inc related code
3000 rem generatemonsters - spawn monsters
3001 mm=0
3002 for i=1 to ri
3003 if rnd(1) <= 0.4 goto 3009:rem do not gen monster 40%
3004 hd(1)=int(rnd(1)*(rm(i,3)-rm(i,1)-2))+rm(i,1)+1:rem spawn x
3005 hd(2)=int(rnd(1)*(rm(i,4)-rm(i,2)-2))+rm(i,2)+1:rem spawn y
3006 gosub 2400:rem check not spawn on item, try again if hit
3007 if hd(3)<>-1 or (hd(1)=p(1) and hd(2)=p(2)) goto 3004
3008 mm=mm+1:m(mm,1)=hd(1):m(mm,2)=hd(2):m(mm,3)=hd(1):m(mm,4)=hd(2):m(mm,5)=i
3009 next i
3010 return

3100 rem moverandom
3101 if m(mi,5)=p(5) then return:rem not for in player room
3102 d=int(rnd(1)*4):ds=d:rem direction,starting direction
3103 hd(1)=m(mi,1):hd(2)=m(mi,2)
3104 if d=0 then hd(1)=hd(1)-1:goto 3108:rem left
3105 if d=1 then hd(1)=hd(1)+1:goto 3108:rem right
3106 if d=2 then hd(2)=hd(2)-1:goto 3108:rem up
3107 if d=3 then hd(2)=hd(2)+1:rem down
3108 gosub 2400:if hd(3)<>-1 goto 3112:rem hit item try again
3109 gosub 1400:if hd(3)=1 goto 3112:rem hit wall try again
3110 m(mi,1)=hd(1):m(mi,2)=hd(2):rem move monster
3111 return
3112 d=(d+1)-int((d+1)/4)*4:rem d+1 mod 4
3113 if d<>ds goto 3103:rem try next dir
3114 return

3200 rem movetoplayer - with light move away, else attack
3201 d=1:if l>0 then d=-1
3203 cx=mo(mi,1)-p(1):cy=mo(mi,2)-p(2):rem dist to player
3204 if cx=0 and cy=0 then return:rem hit player
3205 hd(1)=m(mi,1):hd(2)=m(mi,2)
3206 if abs(cx)>abs(cy) and cx>0 then hd(1)=hd(1)-d:goto 3211
3207 if abs(cx)>abs(cy) and cx<0 then hd(1)=hd(1)+d:goto 3211
3209 if cy>0 then hd(2)=hd(2)-d:goto 3211
3210 hd(2)=hd(2)+d
3211 gosub 2400:if hd(3)<>-1 goto 3215:rem hit item try random
3212 gosub 1400:if hd(3)=1 goto 3215:rem hit wall try random
3213 m(mi,1)=hd(1):m(mi,2)=hd(2):rem move monster
3214 return
3215 gosub 3100:return:rem hit item/wall try random

3300 rem movemonsters
3301 for i=1 to mm
3302 mi=i
3303 if m(mi,5)=p(5) then gosub 3200:goto 3305:rem same room move player
3304 gosub 3100:rem else move rand
3305 next i
3306 return

3400 rem hitmonster
3401 gosub 1600:z=hd(3):hd(3)=-1:rem get room
3402 for i=1 to mm
3403 if m(i,5)<>z goto 3406:rem not same room
3404 cx=abs(hd(1)-m(i,1)):cy=abs(hd(2)-m(i,2)):rem manhattan distance
3405 if cx<4 and cy<4 goto 3408:rem hit monster
3406 next i
3407 return
3408 if cx>=cy then hd(3)=cx:return
3409 hd(3)=cy:return

3499 rem graphics.inc related code
3500 rem drawroom
3501 if rm(ri,5)<>1 then return: rem no draw not discovered room
3502 hd(1)=rm(ri,1):hd(2)=rm(ri,2):gosub 910:rem set cursor
3503 xw$=chr$(166):for i=hd(1)+1 to rm(ri,3):xw$=xw$+chr$(166):next i
3504 print xw$;
3505 for i=rm(ri,2)+1 to rm(ri,4)-1
3506 hd(1)=rm(ri,1):hd(2)=i:gosub 910:print chr$(166);
3507 hd(1)=rm(ri,3):hd(2)=i:gosub 910:print chr$(166);
3508 next i
3509 hd(1)=rm(ri,1):hd(2)=rm(ri,4):gosub 910:print xw$;
3510 poke 646,5:return

3600 rem drawdoor
3601 if rm(do(di,3),5)=0 and rm(do(di,4),5)=0 then return:rem one must be disc
3602 dc$=chr$(118):if do(di,5)=1 then dc$=" ":rem door symbol
3603 hd(1)=do(di,1):hd(2)=do(di,2):gosub 910:print dc$;
3604 poke 646,5:return

3700 rem drawitem
3701 if it(ii,10)=0 then return:rem no redraw set
3702 it(ii,10)=0
3703 if it(ii,4)=1 then ic$=chr$(5)+chr$(115):goto 3706:rem light-white hrt
3704 if it(ii,4)=2 then ic$=chr$(158)+chr$(122):goto 3706:rem trea-yel coin
3705 ic$="?":rem unknown type
3706 hd(1)=it(ii,1):hd(2)=it(ii,2):gosub 910:print ic$;
3708 poke 646,5:return

3800 rem hideitem
3801 if it(ii,10)=0 then return:rem no redraw set
3802 it(ii,10)=0
3806 hd(1)=it(ii,1):hd(2)=it(ii,2):gosub 910:print " ";
3808 return

3900 rem drawmonster
3901 if p(1)=m(mi,3) and p(2)=m(mi,4) goto 3903:rem player in old spot
3902 hd(1)=m(mi,3):hd(2)=m(mi,4):gosub 910:print " ";
3903 g$=chr$(155)+chr$(34):print chr$(18);:rem inv light gray quote
3904 hd(1)=m(mi,1):hd(2)=m(mi,2):gosub 910:print g$;chr$(146);
3905 m(mi,3)=m(mi,1):m(mi,4)=m(mi,2):rem dx=x,dy=y
3906 poke 646,5:return

3950 rem hidemonster
3951 if p(1)=m(mi,3) and p(2)=m(mi,4) goto 3953:rem player in old spot
3952 hd(1)=m(mi,3):hd(2)=m(mi,4):gosub 910:print " ";
3953 hd(1)=m(mi,1):hd(2)=m(mi,2):gosub 910:print " ";
3954 m(mi,3)=m(mi,1):m(mi,4)=m(mi,2):rem dx=x,dy=y
3955 return

4000 rem drawmonsters
4001 for i=1 to mm
4002 if rm(m(i,5),6)=1 or l>0 then mi=i:gosub 3900:goto 4004:rem show
4003 mi=i:gosub 3950:rem hide
4004 next i
4005 return

4100 rem drawdungeon
4101 for r = 1 to rx:rem rooms
4102 hd(1)=p(3):hd(2)=r:gosub 1700:rem check if player can see
4103 if rm(r,6)<>hd(3) then rm(r,7)=1:rem flag room status changed
4103 rm(r,6)=hd(3):rem set show contents
4104 ri=r:gosub 3500:rem draw room
4105 next r
4106 for di = 1 to dm:gosub 3600:next di:rem doors
4107 for ii = 1 to im:rem items
4108 if it(ii,10)=1 or rm(it(ii,3),7)=1 then it(ii,10)=1:rem redraw on change
4109 if it(ii,5)=1 or rm(it(ii,3),6)<>1 or l=0 then gosub 3800:goto 4111
4110 gosub 3700:rem draw item
4111 next ii
4112 return

4200 rem drawframe
4201 hd(1)=0:hd(2)=0:gosub 910:rem set cursor
4202 xw$=chr$(166):for i=1 to sw-1:xw$=xw$+chr$(166):next i
4203 print xw$;
4204 for i=1 to sh-2
4205 hd(1)=0:hd(2)=i:gosub 910:print chr$(166);
4206 hd(1)=sw-1:hd(2)=i:gosub 910:print chr$(166);
4207 next i
4208 hd(1)=0:hd(2)=sh-1:gosub 910:print left$(xw$,39);
4209 poke 2023,peek(2022):rem poke last to stop scroll
4210 return

4300 rem drawplayer
4301 hd(1)=p(3):hd(2)=p(4):gosub 910:print " ";:rem erase old
4302 hd(1)=p(1):hd(2)=p(2):gosub 910:print chr$(5)+chr$(119);:rem draw
4303 p(3)=p(1):p(4)=p(2):rem dx=x,dy=y
4304 return

4400 rem drawstatus -- showing room for debug
4401 hd(1)=1:hd(2)=sh-1
4402 c$=chr$(166)
4402 for i=1 to sw-4
4403 c$=c$+chr$(166)
4404 next i
4402 gosub 910: print c$;
4403 gosub 910
4404 print "room";p(5);rm(p(5),1);rm(p(5),2);rm(p(5),3);rm(p(5),4);
4405 return