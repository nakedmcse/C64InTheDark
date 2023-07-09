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
14 sw=22:sh=23:rem vic 20 screen wxh
15 lw=3:lh=6:uw=7:uh=10:mw=3:mh=3:rem room sizes
16 no="":ni=0:ad="":ai=0:rem noun, adjective
17 rnd(-ti):rem init random

1000 rem noun set
1001 if ni=0 then no="match":return
1002 if ni=1 then no="candle":return
1003 if ni=2 then no="glow worms":return
1004 if ni=3 then no="branch":return
1005 if ni=4 then no="squash":return
1006 if ni=5 then no="bulb":return
1007 if ni=6 then no="torch":return
1008 if ni=7 then no="rock":return
1009 if ni=8 then no="torch":return
1010 if ni=9 then no="brass lantern":return
1011 if ni=10 then no="painting":return
1012 if ni=11 then no="egg":return
1013 if ni=12 then no="jewel":return
1014 if ni=13 then no="belt buckle":return
1015 if ni=14 then no="casket":return
1016 if ni=15 then no="crystal skull":return
1017 if ni=16 then no="pearl":return
1018 if ni=17 then no="piece of eight":return
1019 if ni=18 then no="fish scale":return
1020 if ni=19 then no="carpenters chalice":return
1021 return

1100 rem adjective set
1101 if ai=0 then ad="glimmering":return
1102 if ai=1 then ad="shimmering":return
1103 if ai=2 then ad="bright":return
1104 if ai=3 then ad="golden":return
1105 if ai=4 then ad="sparkling":return
1106 if ai=5 then ad="battery powered":return
1107 if ai=6 then ad="radiant":return
1108 if ai=7 then ad="luminos":return
1109 if ai=8 then ad="flashing":return
1110 if ai=9 then ad="brilliant":return
1111 if ai=10 then ad="wooden":return
1112 if ai=11 then ad="illustrated":return
1113 if ai=12 then ad="golden":return
1114 if ai=13 then ad="bejeweled":return
1115 if ai=14 then ad="plain":return
1116 if ai=15 then ad="resplendant":return
1117 if ai=16 then ad="ghostly":return
1118 if ai=17 then ad="oozing":return
1119 if ai=18 then ad="gigantic":return
1120 if ai=19 then ad="clockwork":return
1121 return

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
1701 for i = 1 to 40:if do(i,1)=-1 goto 1704
1702 if hd(1)=do(3) and hd(2)=do(4) and do(5)=1 goto 1706
1703 if hd(1)=do(4) and hd(2)=do(3) and do(5)=1 goto 1706
1704 next i
1705 hd(3)=0:return:rem cannot see
1706 hd(3)=1:return:rem can see

1800 rem nextroom - generate next room hd(3) 0 on fail
1801 d=int(rnd(1)*4):rem direction
1802 ds=d: rem starting direction
1803 ta=1: rem try again set true
1804 gn=1: rem generate next
1805 w=int(rnd(1)*(uw-lw))+lw+1
1806 h=int(rnd(1)*(uh-lh))+lh+1
1807 if d=0 gosub 1900 : rem move up
1808 if d=1 gosub 1920 : rem move down
1809 if d=2 gosub 1940 : rem move right
1810 if d=3 gosub 1960 : rem move left 
1811 for o=1 to ri:rem check for overlap
1812 ol(1)=rm(o,1):ol(2)=rm(o,2):ol(3)=rm(o,3):ol(4)=rm(o,4)
1813 ol(5)=rm(ri+1,5):ol(6)=rm(ri+1,6):ol(7)=rm(ri+1,7):ol(8)=rm(ri+1,8)
1814 ol(9)=0:gosub 1300: rem check overlap
1815 if ol(9)=1 gosub 1980: rem fix overlap
1816 if gn=1 then ta=0: goto 1820: rem sucess, so no try again
1817 d = (d+1) - int((d+1)/4) * 4: rem d+1 mod 4
1818 if d=ds then ta=0: rem tried all ordinals
1819 if ta=1 goto 1805 : rem try again if set
1820 if gn=1 then ri = ri+1 : rem increment room index on sucess
1821 if gn=0 then rm(ri+1,1)=-1: rem reset to undefined on fail
1822 return

1900 rem genuproom
1901 rm(ri+1,3)=rm(ri,1):rem x2=crx1
1902 if rm(ri+1,3)-w < 1 then w = rm(ri+1,3)-1
1903 if w<lw then gn=0
1904 rm(ri+1,1)=rm(ri+1,3)-w: rem x1 = x2-w
1905 y=int(rnd(1)*(rm(ri,4)-rm(ri,2)-1))+rm(ri,2)+1:rem cry2-cry1-1
1906 if y-int(h/2) < 1 then h=y
1907 if y-int(h/2)+h >= sh then h=sh-y-1
1908 if h<mh then gn=0
1909 rm(ri+1,2)=y-int(h/2): rem y1
1910 rm(ri+1,4)=rm(ri+1,2)+h: rem y2
1911 return

1920 rem gendownroom -- todo
1921 rm(ri+1,3)=rm(ri,1):rem x2=crx1
1922 if rm(ri+1,3)-w < 1 then w = rm(ri+1,3)-1
1923 if w<lw then gn=0
1924 rm(ri+1,1)=rm(ri+1,3)-w: rem x1 = x2-w
1925 y=int(rnd(1)*(rm(ri,4)-rm(ri,2)-1))+rm(ri,2)+1:rem cry2-cry1-1
1926 if y-int(h/2) < 1 then h=y
1927 if y-int(h/2)+h >= sh then h=sh-y-1
1928 if h<mh then gn=0
1929 rm(ri+1,2)=y-int(h/2): rem y1
1930 rm(ri+1,4)=rm(ri+1,2)+h: rem y2
1931 return

1940 rem genleftroom -- todo
1941 rm(ri+1,3)=rm(ri,1):rem x2=crx1
1942 if rm(ri+1,3)-w < 1 then w = rm(ri+1,3)-1
1943 if w<lw then gn=0
1944 rm(ri+1,1)=rm(ri+1,3)-w: rem x1 = x2-w
1945 y=int(rnd(1)*(rm(ri,4)-rm(ri,2)-1))+rm(ri,2)+1:rem cry2-cry1-1
1946 if y-int(h/2) < 1 then h=y
1947 if y-int(h/2)+h >= sh then h=sh-y-1
1948 if h<mh then gn=0
1949 rm(ri+1,2)=y-int(h/2): rem y1
1940 rm(ri+1,4)=rm(ri+1,2)+h: rem y2
1941 return

1960 rem genrightroom -- todo
1961 rm(ri+1,3)=rm(ri,1):rem x2=crx1
1962 if rm(ri+1,3)-w < 1 then w = rm(ri+1,3)-1
1963 if w<lw then gn=0
1964 rm(ri+1,1)=rm(ri+1,3)-w: rem x1 = x2-w
1965 y=int(rnd(1)*(rm(ri,4)-rm(ri,2)-1))+rm(ri,2)+1:rem cry2-cry1-1
1966 if y-int(h/2) < 1 then h=y
1967 if y-int(h/2)+h >= sh then h=sh-y-1
1968 if h<mh then gn=0
1969 rm(ri+1,2)=y-int(h/2): rem y1
1960 rm(ri+1,4)=rm(ri+1,2)+h: rem y2
1961 return

1980 rem fixoverlap
1981 if rm(ri+1,4)>rm(ri,2) then rm(ri+1,4)=rm(ri,2):goto 1985
1982 if rm(ri+1,2)<rm(ri,4) then rm(ri+1,2)=rm(ri,4):goto 1985
1983 if rm(ri+1,3)>rm(ri,1) then rm(ri+3,1)=rm(ri,1):goto 1985
1984 if rm(ri+1,1)<rm(ri,3) then rm(ri+1,1)=rm(ri,3)
1985 rw = rm(ri+1,3)-rm(ri+1,1):rh = rm(ri+1,4)-rm(ri+1,2)
1986 if rw<mw or rh<mh then gn=0: rem overlap cannot be fixed by clip
1987 return