/****************************************************************************
** Form implementation generated from reading ui file 'mainwindow.ui'
**
** Created: Wed Feb 20 14:30:26 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "uzoomain.h"

#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qtabwidget.h>
#include "conditionlistview.h"
#include "searchlistbox.h"
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

static const char* const image0_data[] = { 
"128 128 256 2",
"Qt c None",
"bA c #1e0d79",
"ay c #281ba9",
"bv c #2f042a",
"aj c #3a2dbb",
"ao c #483bbe",
"bS c #4f2a3b",
"ad c #5246c8",
"bz c #575757",
"#M c #5c4fdf",
"#8 c #5e5cb3",
"#F c #665bd5",
"#V c #67108e",
"#c c #676767",
"#L c #6a5deb",
"ba c #6c0030",
"aP c #6e69ce",
"a4 c #70294a",
"#9 c #724477",
"## c #747474",
"#7 c #786cf5",
"a3 c #7a71b7",
"#Z c #7d637d",
"#. c #7f7f7f",
"aH c #8082ba",
".9 c #848484",
"#G c #867afa",
"bl c #885b9f",
"#O c #897399",
".6 c #8c8c8c",
"#Q c #8d04ca",
"a# c #8e8495",
"#H c #8e87d3",
"av c #8f8dbb",
"#K c #9421c5",
"bT c #94828b",
".5 c #949494",
"af c #954bc0",
"#S c #958afd",
".4 c #999999",
"aO c #9a1859",
"#P c #9b9ac2",
"bB c #9d5bd9",
"#B c #a097fc",
"aW c #a1899b",
".1 c #a3a3a3",
"bD c #a7a9c4",
"bd c #a9447b",
"bk c #aa90a9",
"#1 c #aaa2fe",
"#r c #ab32df",
".X c #acacac",
"bn c #ae7b91",
"bL c #b1a9ad",
"#Y c #b20ef3",
".V c #b2b2b2",
"be c #b3abfd",
"bH c #b3b5cc",
"#x c #b59ee1",
"#n c #b62cf0",
"#E c #b6a4bf",
"b. c #b6b2e1",
".U c #b6b6b6",
"bt c #b8b4b6",
"bY c #b955a5",
"#A c #bab2fd",
".T c #bababa",
".S c #bdbdbd",
"aJ c #bdbed1",
"#p c #c045f2",
".R c #c0c0c0",
"ai c #c2bcfd",
"#s c #c429fc",
".Q c #c4c4c4",
"bX c #c7c0c2",
"ae c #c7c5d5",
".P c #c7c7c7",
"au c #c8c2ff",
"#i c #c966f2",
".O c #cacaca",
"bc c #cb046d",
"#q c #cbabd9",
".3 c #cbcbcb",
"#C c #cbcbdd",
"#D c #cc41ff",
".Y c #cccccc",
"#u c #cd56fe",
"#o c #cd71f6",
".N c #cdcdcd",
".M c #d0d0d0",
"aw c #d1bec7",
"aI c #d1cafd",
".L c #d3d3d3",
"#2 c #d3d3df",
"a1 c #d4d2d3",
".K c #d4d4d4",
".J c #d5d5d5",
"bg c #d62f86",
"#w c #d664fe",
"#v c #d7bce3",
".I c #d7d7d7",
"#J c #d87afe",
"b# c #d8d2db",
".H c #d8d8d8",
"bw c #d957a2",
"#k c #d9cbe0",
"at c #d9d4ff",
"ak c #d9d9e3",
".G c #dadada",
".F c #dbdbdb",
"ah c #dc2285",
"aD c #dc4e99",
".E c #dcdcdc",
".D c #dddddd",
"#N c #de8bff",
".C c #dedede",
"ag c #dfc9d4",
".B c #dfdfdf",
".A c #dfe0e0",
".u c #e0e0e0",
"#W c #e0e0e7",
"an c #e1dbff",
".t c #e1e1e1",
".2 c #e1e2e1",
".0 c #e1e2e2",
"#m c #e2dae2",
".Z c #e2e2e1",
".s c #e2e2e2",
"as c #e3e1e1",
".v c #e3e3e3",
"aX c #e3e4e3",
"#U c #e495ff",
".r c #e4e4e4",
"#f c #e4e4e5",
"aT c #e5ccf1",
"ap c #e5e3e4",
"#6 c #e5e5e4",
".7 c #e5e5e5",
"aA c #e678fe",
"#j c #e6a8ff",
"#I c #e6e2ea",
".q c #e6e6e6",
"bh c #e7e4e5",
".w c #e7e7e7",
"#d c #e7e8e7",
"#b c #e7e8e8",
"#y c #e7e8ed",
"#5 c #e8cfdb",
"#z c #e8dee6",
"#e c #e8e8e7",
"#a c #e8e8e8",
"#T c #e9bafd",
"az c #e9e7fd",
"#h c #e9e8e9",
".p c #e9e9e9",
"#g c #e9eae9",
"#l c #eaeae9",
".x c #eaeaea",
"#4 c #ebe5ed",
"aR c #ebe9ef",
"#t c #ebebeb",
"bi c #ecebec",
"aY c #ecebef",
".W c #ececec",
"aq c #ed4aa1",
"aL c #edd9e4",
"bf c #ede6e9",
"#3 c #ededec",
".o c #ededed",
"bm c #eee7ea",
"#R c #eeeeed",
".y c #eeeeee",
".i c #efefef",
"aK c #eff0ef",
"a8 c #f00f87",
"bF c #f0e9ed",
"a9 c #f0ebf2",
"bb c #f0eff2",
"aS c #f0f0ef",
".h c #f0f0f0",
"al c #f12993",
"aB c #f153a9",
"aG c #f1f0f1",
".g c #f1f1f1",
"#X c #f2cdff",
"aQ c #f2f1f3",
"ax c #f2f2f1",
".f c #f2f2f2",
"aF c #f2f2f3",
"bJ c #f2f2f4",
"bj c #f2f3f3",
"ac c #f3429f",
"bq c #f3a8ff",
"aE c #f3f2f2",
"bs c #f3f2f3",
".j c #f3f3f3",
"by c #f3f3f5",
"bp c #f4b9ff",
"bQ c #f4f1f2",
"bM c #f4f2ff",
"bR c #f4f4f3",
".e c #f4f4f4",
"bK c #f4f4f5",
"bG c #f4f4f6",
"a5 c #f4f5f4",
"a2 c #f4f5f5",
"bW c #f5f4f4",
"bE c #f5f5f4",
".k c #f5f5f5",
"bo c #f5f5f6",
"bu c #f5f6f5",
"a. c #f6d7ff",
"bV c #f6f6f5",
".d c #f6f6f6",
"bC c #f6f6f7",
"bZ c #f6f7f6",
"br c #f6f7f7",
"b6 c #f7f6f6",
".l c #f7f7f7",
"b5 c #f7f8f7",
"bI c #f7f8f8",
"aa c #f86aba",
"bU c #f8f7f7",
"bN c #f8f7ff",
"bx c #f8f8f7",
".z c #f8f8f8",
".c c #f9f9f9",
".n c #fafafa",
"am c #fb1c98",
"ar c #fb45a5",
".b c #fbfbfb",
"b0 c #fbfbfc",
"b3 c #fbfcfb",
"b8 c #fbfcfc",
"#0 c #fce9fb",
"b1 c #fcfbfb",
"b4 c #fcfbfc",
"b2 c #fcfcfb",
".m c #fcfcfc",
"a6 c #fd7cc3",
".a c #fdfdfd",
"b7 c #fdfefe",
"aC c #fe35a6",
"aZ c #fe4cb0",
"aU c #fe53b0",
"aM c #fe5ab1",
"aN c #fe60b8",
"b9 c #fefdfe",
".# c #fefefe",
"aV c #ff8cd0",
"a7 c #ff9ed3",
"a0 c #ffaede",
"bP c #ffc0e5",
"ab c #ffceea",
"bO c #ffd8ef",
".8 c #ffffff",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.#.a.b.c.d.e.f.g.h.h.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.h.h.h.g.f.j.k.l.c.b.m.#.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQt.#.a.n.l.f.o.p.q.r.s.t.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.t.t.s.s.v.r.w.x.y.f.k.z.b.a.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQt.#.#.b.l.g.x.u.u.u.u.A.B.B.B.B.B.B.B.B.C.C.C.C.C.D.E.E.E.F.G.G.G.G.H.H.I.J.J.J.J.J.K.L.L.L.M.M.M.N.N.O.P.Q.R.R.S.T.U.V.T.R.M.D.q.W.f.d.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQt.#.m.c.f.x.B.u.u.u.u.u.u.B.u.B.u.B.u.A.B.C.C.C.C.C.D.E.D.D.E.G.G.G.H.G.G.I.I.J.J.J.J.K.K.K.L.L.M.M.M.N.O.P.Q.R.R.S.T.U.V.V.X.U.Y.D.w.i.e.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQt.#.b.d.o.s.L.t.t.t.t.t.t.t.t.t.t.t.u.t.u.u.u.u.B.B.B.C.D.D.D.E.F.F.G.G.G.G.G.H.H.I.J.J.J.K.K.L.L.L.M.M.M.Y.P.P.Q.R.S.T.U.V.X.X.X.Q.K.r.o.e.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQt.#.n.e.p.G.O.s.Z.t.t.t.t.t.t.t.0.s.t.t.t.t.t.u.u.B.B.B.C.D.D.D.E.F.F.G.G.G.G.G.H.H.I.J.J.J.K.K.L.L.L.M.M.M.Y.P.P.Q.R.S.T.U.V.X.1.X.S.N.s.W.e.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQt.#.c.f.q.J.R.s.s.s.t.2.t.t.t.t.s.s.s.s.t.t.t.t.u.u.B.B.B.C.D.D.D.E.F.F.G.G.G.G.G.H.H.I.J.J.J.K.K.L.L.L.M.M.M.O.P.P.R.S.T.U.V.X.X.1.X.R.N.s.W.e.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.c.g.r.M.T.s.s.s.s.s.s.s.t.t.s.s.s.s.s.t.t.t.t.u.u.B.B.B.B.C.C.C.D.E.E.F.G.G.G.G.H.H.I.J.J.J.J.J.K.L.L.L.M.N.3.P.P.R.S.T.U.V.X.1.1.V.R.N.s.o.e.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.c.h.s.N.U.s.s.s.s.s.s.s.s.s.s.s.s.s.s.s.t.t.t.t.u.u.B.B.B.B.C.C.C.D.E.E.F.G.G.G.G.H.H.I.J.J.J.J.J.K.L.L.L.M.N.O.P.Q.R.S.U.V.X.1.1.1.S.R.N.v.o.e.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.h.t.Y.V.s.s.s.s.s.s.s.s.s.s.s.s.s.s.s.s.t.t.t.t.u.B.B.B.B.B.C.C.C.D.E.E.F.G.G.G.G.H.I.I.J.J.J.J.J.K.L.L.L.M.N.O.P.R.S.T.V.X.1.1.4.X.P.R.N.v.o.e.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.s.s.s.s.t.u.u.u.u.B.C.C.C.D.E.E.F.G.G.G.G.G.H.H.I.I.J.J.J.K.L.L.M.M.N.O.P.R.T.U.V.X.1.4.4.Q.O.R.N.r.o.k.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.s.s.s.s.t.u.u.u.u.B.C.C.C.D.E.E.F.G.G.G.G.G.H.H.I.I.J.J.J.K.L.L.M.N.3.P.Q.R.T.V.X.1.4.5.X.L.O.R.N.r.o.k.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.s.s.s.s.t.u.u.u.B.B.C.C.D.D.E.E.F.G.G.G.G.G.H.H.I.I.J.J.J.K.L.L.M.N.O.Q.R.T.V.X.1.4.5.5.D.L.O.R.Y.r.o.k.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.s.s.s.s.t.u.u.u.B.B.B.B.C.C.D.D.E.F.F.G.G.G.H.H.I.J.J.J.J.J.L.L.M.N.O.Q.S.U.X.1.4.5.6.H.D.L.O.R.Y.r.o.k.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.v.s.s.s.s.t.u.u.u.B.B.B.B.C.D.D.D.E.F.F.G.G.G.H.H.I.J.J.J.J.K.L.L.M.3.P.R.U.X.1.4.5.6.O.7.D.L.O.R.Y.r.o.k.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.v.v.v.v.s.t.t.t.u.u.B.B.C.D.D.D.E.F.F.G.G.G.G.H.H.I.I.J.J.K.L.M.N.P.R.T.V.1.4.5.6.S.o.7.D.L.O.R.Y.r.o.k.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.v.v.v.v.s.t.t.t.u.u.B.B.C.D.D.D.E.F.F.G.G.G.G.H.H.I.I.J.K.K.M.M.O.Q.T.V.X.4.5.6.V.e.o.7.D.L.O.R.3.r.o.k.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.v.v.v.v.s.t.t.t.u.u.u.u.B.C.C.C.D.E.E.F.G.G.G.H.H.I.J.J.K.L.M.Y.P.R.U.X.1.5.6.1.n.e.o.7.D.L.O.R.3.r.o.k.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.r.v.v.v.v.s.t.t.t.u.u.u.u.B.C.C.C.D.E.E.F.G.G.G.H.H.I.J.K.L.M.N.P.R.U.X.1.5.6.4.8.n.e.o.7.D.L.O.R.3.r.o.k.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.r.r.r.r.v.s.s.s.t.u.u.u.B.C.C.C.D.E.E.F.G.G.G.G.G.I.J.K.M.M.O.R.T.V.1.4.6.4.8.8.n.e.o.7.D.L.O.R.3.r.o.k.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.r.r.r.r.v.s.s.s.t.u.u.u.B.C.C.C.D.E.E.F.G.G.G.G.H.J.J.L.M.O.Q.T.V.1.4.6.6.8.8.8.n.e.o.7.D.L.O.R.3.r.o.k.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.r.r.r.r.v.v.s.s.s.t.u.u.u.B.C.C.C.D.E.E.F.G.G.G.H.H.J.L.M.O.Q.S.V.1.4.6.6.8.8.8.8.n.e.o.7.D.L.O.R.3.r.o.k.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.r.r.r.r.v.v.s.s.s.t.u.u.u.u.B.B.B.C.D.D.E.F.F.G.H.I.K.M.Y.Q.S.V.X.4.6.9.8.8.8.8.8.n.e.o.7.D.L.O.R.Y.r.o.k.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.q.q.7.7.7.7.7.7.7.7.q.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.7.r.r.r.r.v.v.s.s.s.t.u.u.u.u.B.B.B.C.D.D.E.F.G.G.H.J.L.Y.P.S.U.X.4.5.9.8.8.8.8.8.8.n.e.o.7.D.L.O.R.Y.r.o.k.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.w.q.q.q.q.q.q.q.q.q.w.q.q.q.q.q.q.q.q.q.q.q.q.q.q.q.q.q.q.q.7.7.7.7.r.r.v.v.v.s.t.t.t.u.B.B.B.C.D.D.E.G.G.G.J.L.M.P.R.U.X.1.5.9.8.8.8.8.8.8.8.n.e.o.7.D.L.O.R.Y.r.o.k.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.w.w.w.w.w.w.q.q.q.w.w.w.w.q.q.q.q.q.q.q.q.q.q.q.q.q.q.q.q.q.q.7.7.7.7.r.r.v.v.v.s.t.t.t.u.B.B.B.C.D.D.F.G.G.J.L.N.O.R.T.X.1.5.6.8.8.8.8.8.8.8.8.n.e.o.7.D.L.O.R.Y.r.o.k.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.w.w.w.w.w.w.w.w.q.w.w.w.w.w.q.w.w.q.q.q.w.q.q.q.q.q.q.q.q.q.q.q.7.7.7.7.r.r.v.v.v.s.t.t.t.u.u.u.B.B.C.D.E.G.H.J.M.3.Q.T.X.1.5.6.8.8.8.8.8.8.8.8.8.n.e.o.7.D.L.O.R.N.r.o.e.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.w.w.w.w.w.w.w.w.w.w.w.w.w.w.w.w.w.w.w.w.w.w.q.w.q.q.q.q.q.q.q.q.q.7.7.7.7.r.r.v.v.v.s.t.t.t.u.u.u.B.C.D.D.F.G.J.M.O.Q.T.X.1.4.6#.######.9#.#.#..6.1.X.R.M.r.D.L.O.R.N.r.o.e.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#b#b.w.w.w.w.w.w.w.w.w.w.w.q.q.q.q.7.7.r.r.r.v.s.s.s.t.u.u.B.D.D.E.G.J.M.Y.Q.T.V.1.4.6.9#.###c#c#c#c#c#c#c#c#c####.5.X.P.O.R.N.v.o.e.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#b.w#d.w.w.w.w.w.w.w.q.q.q.q.7.7.r.r.r.v.s.s.s.t.u.u.C.D.E.F.H.L.N.P.S.V.1.4.5.6#.#######c#c#c#c#c#########.#..9.1.S.R.N.v.o.e.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.p#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a.w.w.w.w.w.w.q.q.q.q.7.7.r.r.r.v.s.s.s.t.u.B.B.D.E.G.J.M.O.R.U.X.1.4.6.9#.#.###################.#.#..9.6.6.1.S.N.v.o.e.c.a.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.p.p.p.p.p.p#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a.w#e.w.w.w.w.q.q.q.7.7#f.r.r.v.v.s.s.t.u.B.C.E.G.I.M.O.Q.T.V.1.4.5.6.9.9#.#.#.#.#.#.#.#.#..9.9.9.6.6.6.5.4.S.K.r.y.d.n.a.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.p.p.p.p.p.p.p.p#a.p.p.p.p#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#a#e.w#d.w.q.q.q.q.7.r.r.r.v.v.s.s.t.B.C.D.F.I.L.N.Q.S.U.X.1.4.5.5.6.6.6.6.6.6.6.6.6.6.6.6.6.6.5.5.4.4.1.Q.H.q.h.l.b.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.x.x.x.x.x.x.x.x.x.x.x.x.x#g#g.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p#h#a#a.w.w.w.w.q.7.7.7.7.r.u#i#j#i#k.C.E.H.K.M.O.R.T.V.X.1.1.4.4.5.5.5.5.5.5.5.5.5.5.5.4.4.4.4.4.4.4.X.P.F.p.j.c.a.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x#l.x.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p#a#a.w.w.w.q.q.q.7.7#m#n#o#p#q.B.D.G.J.M.N.P.R.T.V.X.X.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.R.M.t.o.d.b.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p#a#a#a.w.w.q.q.7#m#r#s#n#q.u.C.D.G.J.M.Y.P.R.S.T.V.V.V.X.X.X.X.V.X.X.V.X.X.X.X.X.X.1.1.1.1.1.T.P.H#a.j.c.a.#QtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V#t#t#t.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x#l.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p#a#a#a.w.w.q.q#m#r#u#n#v.Z.u.C.F.H.K.M.Y.P.Q.R.S.T.T.T.T.T.T.T.T.T.T.T.U.U.V.V.V.V.X.X.X.X.X.P.M.s.i.l.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V#t#t#t#t#t#t.x.x.x#t#t.x.x.x.x.x.x.x.x.x.x.x.x.x.x.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p.p#a#a#a#a.w.q#m#n#w#s#x.v.t.u.C.E.H.J.M.N.Y.P.P.Q.Q.R.Q.R.Q.Q.Q.Q.R.R.R.S.S.T.U.U.U.V.V.V.V.S.P.E#t.k.b.#QtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.W.W.W.W.W.W.W.W#t.W.W#t#t#t#t#t#t#t#t#t#t#t#t#t#t#t#y.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.p.p.p#a#a#z#n#w#s#r.r.v.s.B.B.E.H.J.K.L.M.N.Y.3.3.O.3.3.3.3.O.O.O.P.P.Q.R.R.S.S.T.U.V.V.U.R.I#a.e.n.#QtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.W.W.W.W.W.W.W.W.W.W.W.W.W.W#t#t#t#t#t#t#t#t#t#t#t#x#A#B#C.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.p.p.p#h#z#n#o#s#D#E.r.v.s.B.B.E.F.H.I.K.K.L.L.L.M.M.M.M.M.M.M.M.N.Y.O.P.Q.Q.R.R.S.T.U.U.S.L.7.f.c.#QtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.W.W.W.W.W.W.W.W.W.W.W.W.W.W.W.W.W#t#t#t#t#t#t#t#t#F#B#G#H#t#t.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.p.p.p#I#n#J#D#w#K.t.r.v.s.u.B.C.D.F.G.G.H.H.I.J.I.J.J.J.J.J.K.K.L.M.N.Y.P.P.Q.R.S.T.T.T.M.v.g.c.aQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.o.o.W.W.W.W.W.W.W.W.W.W.W.W.W.W.W.W.W#t#t#t#t#t#t#F#L#M#H#t#t#t#t.x.x.x.x.x.x.x.x.x.x.x.x.x.x.p.p#z#n#J#D#N#s#O.7.r.r.s.t.u.B.C.D.D.E.F.F.F.G.G.G.G.H.I.I.J.J.K.L.M.N.O.P.Q.R.R.T.U.N.s.h.c.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.y.y.y.y.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.o.W.W.W#F#G#L#P.W.W.W.W.W.W#t#t#t#t#t#t#t#t#t#t#t#t#t.x#I#n#J#D#j#w#Q.R.7.7.r.r.s.s.t.t.u.B.B.C.C.E.E.F.F.G.G.G.H.I.J.J.L.L.N.3.O.P.R.R.U.N.s.h.c.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.y.y.y.y.y.y#R.o.o.y.y.o.o.o.o.o.o.o.o.o.o.o.o.W.W#F#S#L#H.W.W.W.W.W.W.W.W#t#t#t#t#t#t#t#t#t#t#t#t#I#n#N#D#T#U#s#V.u.q.7.7.r.v.v.v.s.t.t.u.B.C.C.D.D.E.F.G.G.G.H.I.J.K.L.M.Y.O.P.Q.V.Y.t.h.c.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.y.y.y.y.y.y.y.y.y.y.y.y.y.o.o.o.o.o.o.o.o.o.o.o.o#F#B#L#L#W.W.W.W.W.W.W.W.W.W#t#t#t#t#t#t#t#t#t#t#I#n#N#D#N#X#w#Y#Z.w.q.q.q.r.v.v.v.s.t.u.u.B.B.C.D.D.E.F.F.G.G.G.H.J.J.L.M.N.O.P.V.Y.t.h.c.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.y.y.y.y.y.y.y.y.y.y.y.y.y.y.y.o.o.o.o.o.o.o.o.o.o#F#B#L#G#H.W.W.W.W.W.W.W.W.W.W.W#t#t#t#t#t#t#t#t#I#n#N#u#s#0#j#D#Q.R.w.q.q.q.7.r.r.r.v.s.s.t.u.u.B.C.C.D.E.E.E.G.G.G.I.J.L.M.N.O.V.Y.t.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.h.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.y.y.y.y.y.y.y.y#F#1#L#S#M#2.o.o.o.o.o.o.o.o.o.o.o#3.W.W.W.W.W.W#4#n#N#w#V#J#0#N#s#V.q#a.w.w.w#m#5#z#6.r.v.v.s.t.u.u.B.C.C.D.E.F.G.G.G.I.J.L.M.N.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.h.h.h.h.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.y.y.y.y.y#F#1#7#1#G#8.y.y.o.o.o.o.o.o.o.o.o.o.o.o.W.W.W.W#4#n#U#w#9#Q#ja.#w#Ya#.p#a.w#5aaabac#m.7.r.v.s.s.t.t.u.B.B.C.D.E.F.F.G.G.I.J.L.M.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.h.h.h.h.h.h.i.i.i.h.h.i.i.i.i.i.i.i.i.i.i.i.i.y.y#F#1#7#A#Bad#P.y.y.y.o.o.o.o.o.o.o.o.o.o.o.o.W.W#4#n#U#waeaf#s#j#T#D#V.B.p#aagahacah#m.7.7.r.v.v.s.t.t.u.B.C.C.D.E.E.F.G.G.I.J.L.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.h.h.h.h.h.h.h.h.h.h.h.h.h.i.i.i.i.i.i.i.i.i.i.i.i#F#1#7#Aai#7ajak.y.y.y.y.o.o.o.o.o.o.o.o.o.o.o.o#4#n#U#i#v.7#r#D#U#U#s#O.p.pagalamah#m.7.7.7.r.v.v.s.t.t.u.B.B.C.D.D.E.F.G.G.I.J.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.h.h.h.h.h.h.h.h.h.h.h.h.h.h.h.h.i.i.i.i.i.i.i.i.i#F#1#7#San#B#Mao.y.y.y.y.y.y.o.o.o.o.o.o.o.o.o.o#4#n#U#i#v.W.C#i#D#U#w#Qap.pagaqarahas.q.7.7.r.r.v.v.s.t.t.u.B.B.C.D.E.E.F.G.G.I.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.f.f.g.g.g.g.g.g.g.g.g.g.g.g.g.g.g.g.h.h.h.h.h.h.h#F#1#S#Matau#Gajav.i.i.i.i.i.i.i.y.y.y.y.y.y.y.y#4#n#U#i#v.o.o#m#n#D#U#s#E.x#5acaqamaw#a.w.q.q.7.r.r.r.v.s.s.t.u.B.B.C.D.D.F.F.G.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.f.f.f.fax.g.g.g.g.g.g.g.g.g.g.g.g.g.g.g.h.h.h.h.h#F#1#Bay#7az#A#Layak.i.i.i.i.i.i.i.i.y.y.y.y.y.y#4#n#U#o#v.o.o.o#k#Y#waAaf#t#5aqaBaCaD#a#a.w.q.q.7.r.r.r.v.s.t.t.u.u.B.C.D.E.E.F.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.f.f.f.f.f.f.f.g.g.f.f.g.g.g.g.g.g.g.g.g.g.g.h.h.h#F#1#Baoay#Ban#B#M#8.i.i.i.i.i.i.i.i.i.i.i.y.y.y#4#n#U#i#v.y.o.o.o#E#Y#U#r.x#5araBaCaCaw#a#a.w.q.q.7.r.r.r.v.s.s.t.u.u.B.C.D.D.E.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.faE.faF.faF.f.faF.f.f.f.f.g.g.g.g.g.g.g.g.g.g.gaG#F#1#B#HaH#M#1aI#GajaJ.i.i.i.i.i.i.iaK.i.i.i.y.y#4#n#U#i#v.i.y.y.o.o#9#u#u#IaLaraMaraNaO.q#a#a.w.q.q.7#f.r.r.v.s.s.t.t.u.B.B.D.D.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.e.e.e.e.e.e.e.e.e.e.e.e.e.e.j.j.j.j.j.j.j.j.j.j.f#F#1#B#H.faP#7#1#A#7adaQ.g.g.g.g.g.g.g.g.g.g.h.haR#n#U#i#v.h.haS.i.i.N#K#waT#zaqaNaUaVamaW.x.x.x.p#a#a.w.q.q.7.raX.v.s.t.t.u.B.C.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.e.e.e.e.e.e.e.e.e.e.e.e.e.e.e.e.j.j.j.j.j.j.j.j.j#F#1#B#H.faY#G#G#1#Bao#C.f.g.g.g.g.g.g.g.g.g.g.gaR#n#U#o#v.h.h.h.h.h.i#V#w#T#zacaNaZa0aZaOa1.x.x.x.p#a#a.w.q.q.7.r.r.v.s.t.t.u.B.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.k.k.ea2.e.e.e.e.e.e.e.e.e.e.e.e.e.e.e.j.j.j.j.j.j#F#1#B#H.j.faR#7#L#1#7a3.f.f.fax.g.g.g.g.g.g.g.gaR#n#U#o#v.h.h.h.h.h.h#O#DaT#zacaaaCabaVama4#h.x.x.x.p#a#a.w.q.q.7.7.r.v.s.0.t.u.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.k.k.k.k.k.k.e.e.ea5.e.e.e.e.e.e.e.e.e.e.e.e.j.j.j#F#1#B#H.j.j.j#Iad#7#1ad.g.f.f.f.f.f.g.g.g.g.g.gaR#n#U#o#v.h.h.h.h.h.h#E#s#4aLaca6ala7abaUa8#.#t.x.x.x.p#a#a.w.q.q.q.7.r.v.s.s.t.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.k.k.k.k.k.k.k.k.k.k.k.k.e.e.e.e.e.e.e.e.e.e.e.e.j#F#1#B#H.j.j.j.j#Caj#1#L#2.f.f.f.f.f.f.f.g.g.g.ga9#n#U#o#v.g.h.h.h.h.hae#sa9#zacaVacah#0a7aCaO.3#t.x.x.x.p#a#a.w.q.q.7.r.r.v.v.t.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.k.k.k.k.k.k.k.k.k.k.k.k.k.k.e.e.e.e.e.e.e.e.e.e.e#F#1#B#H.j.j.j.j.ja3#L#Sb..f.f.f.f.f.f.f.f.f.g.ga9#n#U#o#v.g.g.gaG.h.hb##u.haLacaVaDbaa6#0a6a8a4.p#t.x.x.p.p#a#a.w.q.q.7.r.r.v.v.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.d.d.d.d.d.d.d.d.d.d.d.d.d.d.d.d.k.k.k.k.k.k.k.k.k#F#1#B#H.e.e.e.e.e#yaj#B#x.j.j.j.j.j.j.j.j.j.j.fa9#n#U#i#v.f.f.f.f.f.g.hbb.gaLacaVaq#Za8a7abaUbc.1.W.W#t#t.x.x.p.p#a.w.w.q.7.7.v.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.l.d.d.d.d.d.d.d.d.d.d.d.d.d.d.d.d.d.d.k.k.k.k.k.k#F#1#B#H.k.e.e.e.e.e#8#G#B.e.e.j.j.j.j.j.j.j.j.ja9#n#N#i#v.f.f.f.f.f.f.f.g.gaLacaVaqapbdama7a0aCaO.7.W.W#t#t.x.p.p.p#a.w.w.q.7.7.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.l.l.l.l.l.d.d.d.d.d.d.d.d.d.d.d.d.d.d.d.d.k.k.k.k#F#1#B#H.k.k.k.e.e.eaJ#Lbe.e.e.e.e.j.j.j.j.j.j.ja9#n#J#p#v.f.f.f.f.f.f.f.f.faLacaVaqbf#hbgaCaVa6a8aW.o.W.W#t#t.x.p.p.p#a.w.w.q.7.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.l.l.l.l.l.l.l.d.d.l.l.d.d.d.d.d.d.d.d.d.d.d.d.d.k#F#1#1#H.k.k.k.k.k.k#Wadai.e.e.e.e.e.e.j.j.j.j.ja9#n#J#p#v.j.f.f.f.f.f.f.f.faLacaVaDbf.gbhaBaCaVaZaObi.o.W.W#t#t.x.p.p.p#a.w.w.q.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.l.l.l.l.l.l.l.l.l.l.l.l.l.d.d.d.d.d.d.d.d.d.d.d.d#F#1#1#H.k.k.k.k.k.kaRadaI.e.e.e.e.e.e.e.e.jaQaQbb#n#w#n#v.j.jbj.f.f.f.f.f.faLacaVaDbf.g.g#zalaCaVa8aw.y.y.W.W#t#t.x.p.p.p#a.w.w.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.d.l.l.l.l.l.l.l.l.l.l.l.l.l.l.l.d.d.d.d.d.d.d.d.d#F#1#B#H.k.k.k.k.k.kbbaPaz.k.e.e.e.e.e.ubkbl#9#Vbl#p#D#n#v.j.j.j.j.j.f.f.f.faLacaVaDbm.g.g.gagbcaaaNbn.y.y.y.o.W#t#t.x.p.p.p#a.w.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.l.l.l.l.l.l.l.l.l.l.l.l.l.l.l.l.l.l.d.d.d.d.d.d.d#M#1#B#Hbo.k.k.k.k.k.kbb.k.k.k.k.eapbl#i#Ta.#Xbp#r#V#Y#p#v.j.j.j.j.j.j.j.f.faLacaVaDbf.f.f.g.gbka8aVbg.i.y.y.y.o.W#t#t.x.p.p.p#a.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.l.z.z.l.l.l.l.l.l.l.l.l.l.l.l.l.l.l.l.l.l.d.d.d.d#M#1#S#H.d.d.d.k.k.k.k.k.k.k.k.k.1afbqbp#U#N#J#w#s#Q#s#p#m.j.j.j.j.j.j.j.j.jaLacaVaDbm.f.f.f.g.ha4aNah.h.i.y.y.y.o.W.W#t.x.p.p.p.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.d.z.z.z.z.z.z.l.l.z.l.l.l.l.l.l.l.l.l.l.l.l.lbr.d#M#1#G#H.d.d.d.d.dbo.k.k.k.k.k#.#r#U#J#o#w#w#u#s#Y#s#w#pbs.e.j.j.j.j.j.j.j.jaLacaVaDbm.f.f.f.f.fbtbgaC.h.i.i.y.y.y.o.W.W.W.x.p.p.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.d.z.z.z.z.z.z.z.z.z.z.z.l.l.l.l.l.l.l.l.l.l.l.l.l#F#B#7#H.d.d.d.d.d.d.d.d.k.ka##V#D#u#u#w#w#u#D#D#u#uaA#q.e.e.e.e.j.j.j.j.j.jaLacaVaDbm.f.f.f.f.f.WaOaC.h.h.i.i.y.y.y.o.W.Wbi#t.x.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.Vbu.z.z.z.z.z.z.z.z.z.z.z.z.z.z.l.l.l.l.l.l.l.l.l.l#F#S#L#H.d.d.d.d.d.d.d.d.d.Mbv#V#s#D#u#u#u#u#w#J#J#N#wak.e.e.e.e.e.e.j.j.j.jaLacaVbwbm.j.f.f.f.f.f#9am.g.h.h.i.i.y.y.y.o.W.W.W#t.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.d.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.zbx.lbyaJa3#8adaPaP#S#L#H.l.l.d.d.d.d.d.d.kbzbA#Q#Y#D#u#w#w#J#N#U#UbpbB#W.g.e.e.e.e.e.e.e.j.jaLacaVbwbm.j.jbs.f.f.fbnam.g.g.g.g.i.i.y.y.y.o.W.W.W.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.k.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.zbC#P#F#Aananat#Gayao#7#H.l.l.l.l.d.d.d.d#abv#Q#Y#D#u#w#J#N#U#j#T#X#o#P#2.h.e.e.e.e.e.e.e.e.eaLacaVbwbm.j.j.j.j.f.fbkam.f.g.g.g.g.i.i.y.y.y.o.W.W.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.e.c.c.c.z.z.z.z.z.z.z.z.z.z.z.zakadbeataibe#B#S#7ajad#G#x.l.l.l.l.l.l.d.d.Cbv#Q#s#w#J#N#j#T#X#X#0#Na3aJak.h.k.k.e.e.e.e.e.e.eaLacaVbwbm.j.j.j.j.j.fawa6.f.f.g.g.g.g.h.i.y.y.y.o.W.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.e.c.c.c.c.c.z.z.z.c.c.z.z.z.zaeajbe#1#S#S#S#G#7#M#M#G#7#y.l.l.l.l.l.l.l.l#y#V#Y#D#J#U#T#X#0#0#0#Ja3bD#C#y.e.k.k.k.kbE.e.e.e.eaLaca6aDbm.j.j.j.j.j.j.j.f.f.f.f.g.g.g.g.h.h.y.y.y.o.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.j.c.c.c.c.c.c.c.c.c.c.c.c.z#2bA#7#G#G#G#S#G#7#7#G#G#B#H.l.l.l.l.l.l.l.l.l.l#Z#s#w#U#Ta.#0#0bqbBa3bDae#W.j.k.k.k.k.k.k.k.e.e.eaLaca6aDbF.e.j.j.j.j.j.j.j.j.f.f.f.g.g.g.g.h.h.i.y.y.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.f.c.c.c.c.c.c.c.c.c.c.c.cbGbAay#L#7#G#G#G#G#G#B#B#B#1bH.lbI.l.l.l.l.l.l.l.l.j#O#raA#U#U#oafa3#PbH#C#IaF.k.k.k.k.k.k.k.k.k.k.kaLaraabgbF.e.e.e.j.j.j.j.j.j.j.j.f.f.g.g.g.g.h.h.i.y.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.g.c.c.c.c.c.c.c.c.c.c.c.cavbAayad#L#7#G#S#S#1bebeaI#G#2bJ.z.z.z.l.l.l.l.l.l.l.l#2#Pavav#PbHaJ#2#WaY.k.d.d.d.d.k.k.k.k.k.k.k.kaLacaUbgbF.e.e.e.e.e.j.j.j.j.j.j.j.j.f.g.g.g.g.h.h.i.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.g.n.c.c.c.c.c.c.c.c.c.c.cbAayao#L#G#S#S#BbeaiauataiaH#2aY.z.z.z.z.z.l.l.l.l.l.l.lbKbb#y#y#yaYaG.k.d.d.d.d.d.d.d.d.k.k.kaGbfbF#zaqarahbF.e.e.e.e.e.e.e.j.j.j.j.j.j.j.f.g.g.g.g.h.h.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.h.n.n.n.c.c.c.c.c.c.c.c.cbAay#M#G#S#1beaiaIatazanaPbH#2bb.z.z.z.z.z.z.z.z.l.l.l.l.l.l.dbo.l.l.l.d.d.d.d.d.d.d.d.d.ebLbdbdbdaOa4aralahbF.e.e.e.e.e.e.e.e.j.j.j.j.j.j.j.j.f.g.g.g.h.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.i.n.n.n.n.n.n.c.c.n.n.c.cayao#L#SbeauatazbMbNataPbDae#IbC.z.z.z.z.z.z.z.z.z.z.l.l.l.l.l.l.l.l.l.l.l.d.d.d.d.d.d.Vbda7bOabbPa0ahbaa8albF.k.k.e.e.e.e.e.e.e.e.j.j.j.j.j.j.j.f.f.g.g.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.i.n.n.n.n.n.n.n.n.n.n.n.n#P#M#S#1auanbMbNaz#S#8#PaJak.j.z.z.z.z.z.z.z.z.z.z.z.z.z.l.l.l.l.l.l.l.l.l.l.l.l.d.o#9aaa0a7a6aaaNara8bcarbgbQ.k.k.k.k.e.e.e.e.e.e.ebR.j.j.j.j.j.j.f.f.g.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.y.n.n.n.n.n.n.n.n.n.n.n.n.naH#M#1aIaIbeaP#8avbHae#WbJ.c.c.c.z.z.z.z.z.z.z.z.z.z.z.z.z.l.l.l.l.l.l.l.l.l.lbibSaZa6aNaNaMaUaCamamaCaNa6.k.k.k.k.k.k.k.e.e.e.e.e.e.e.e.j.j.j.j.j.f.f.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.y.n.n.n.n.n.n.n.n.n.n.n.n.n.n#W#PaHaHavbDaJ#CakaRbC.c.c.c.c.c.c.c.z.z.z.z.z.z.z.z.z.z.z.z.l.l.l.l.l.l.lbsbSbcaCaraUaMaUaraCaZaUaNaU#m.k.k.k.k.k.k.k.k.k.e.e.e.e.e.e.e.j.j.j.j.j.f.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.y.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.zbyaYaY#yaYaQbo.z.c.c.c.c.c.c.c.c.c.c.z.z.z.z.z.z.z.z.z.z.z.z.z.l.l.l.lbTbvbcamaraZaZaUaUaaa6a6a7bw.y.k.d.k.k.k.k.k.k.k.k.e.e.e.e.e.e.e.e.j.j.j.j.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.o.b.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.c.n.n.c.c.c.c.c.c.c.c.c.c.c.c.c.c.z.z.z.z.z.z.z.z.z.z.z.zbU.l.ibvbabcamaCaZaMaaa6aVa7a7a7bk#WbK.d.dbV.k.k.k.k.k.k.k.kbW.e.e.e.e.e.e.j.j.j.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.o.b.b.b.b.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.c.c.c.c.c.c.c.c.c.c.c.c.c.c.z.z.z.z.z.z.z.z.z.z.zbXbvbca8aCaMaaa6aVa7a0bPbPbYaJakaF.d.d.d.dbu.k.k.k.k.k.k.k.k.e.e.e.e.e.e.e.j.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.o.b.b.b.b.b.b.n.n.b.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.c.c.c.c.c.c.c.c.c.c.c.c.c.c.z.z.z.z.z.z.z.z.z.VbabcaCaNa6aVa0bPabbObObw#Pae#I.k.d.d.d.d.d.d.k.k.k.k.k.k.k.k.k.e.e.e.e.e.e.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.o.b.b.b.b.b.b.b.b.b.b.b.b.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.c.c.c.c.c.c.c.c.c.c.c.c.c.z.z.z.z.z.z.z#2aOa8aZa6a7bPbO#0#0bPbYavaJakbb.d.d.d.d.d.d.d.d.d.k.k.k.k.k.k.k.k.e.e.e.e.e.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.o.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.c.c.c.c.c.c.c.c.c.c.c.c.c.z.z.z.z.z.z#Zamaaa7bPbO#0bPaablavbH#2aYbo.l.d.d.d.d.d.d.d.d.d.d.k.k.k.k.k.k.k.k.e.e.e.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.o.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.c.c.c.c.c.c.c.c.c.c.c.c.z.z.z.zboaWbdaNaaaabYblaHbDaeakaY.d.l.l.l.l.d.d.d.d.d.d.d.d.d.d.k.k.k.k.k.k.kbE.j.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.o.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.c.c.c.c.c.c.c.c.c.c.c.c.z.zbCakbHbDbDbHaJ#Cak#I.j.d.l.l.l.l.l.l.l.l.d.d.d.d.d.d.d.d.k.k.k.k.k.k.k.e.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.o.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.c.c.c.c.c.c.c.c.c.c.c.z.z.lbKbbaYaRaYaQbG.l.zbU.l.l.l.l.l.l.l.l.lbZ.d.d.d.d.d.d.d.d.k.k.k.k.k.j.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.o.m.mb0.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.c.c.c.c.c.c.c.c.c.c.c.c.z.z.z.z.z.z.z.z.z.z.z.l.l.l.l.l.l.l.l.l.l.d.d.d.d.d.d.d.d.k.k.k.k.j.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.o.m.m.m.m.m.b.b.bb1.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.c.c.c.c.c.c.c.c.c.c.c.c.z.z.z.z.z.z.z.z.z.z.z.l.l.l.l.l.l.l.l.l.d.d.d.d.d.d.d.d.d.k.k.f.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.o.m.m.m.m.m.m.m.m.m.m.m.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.c.c.c.c.c.c.c.c.c.c.c.z.z.z.z.z.z.z.z.z.z.z.z.l.l.l.l.l.l.l.l.l.d.d.d.d.d.d.d.d.d.f.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.y.m.m.m.m.m.m.m.m.m.m.m.m.m.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.n.c.c.c.c.c.c.c.c.c.c.c.c.z.z.z.z.z.z.z.z.z.zbx.l.l.l.l.l.l.l.lbC.d.d.d.d.d.d.d.g.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.y.m.m.m.m.m.m.m.m.m.m.m.m.m.m.m.m.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.n.n.n.n.n.n.n.n.n.n.n.n.n.n.c.c.c.c.c.c.c.c.c.c.c.z.z.z.z.z.z.z.z.z.z.z.l.l.l.l.l.l.l.l.l.l.d.d.d.d.d.h.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.y.m.m.m.m.m.m.m.m.m.m.m.m.m.m.m.m.m.m.m.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.n.n.n.n.n.n.n.n.n.n.n.n.n.n.c.c.c.c.c.c.c.c.c.c.c.z.z.z.z.z.z.z.z.z.z.z.l.l.l.l.l.l.l.l.l.d.d.d.d.h.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.y.m.a.m.m.m.m.a.m.a.a.m.m.a.m.m.m.m.a.m.m.m.m.mb2.b.bb3.b.b.mb3b4b3.b.b.bb0b3.b.b.b.n.b.n.n.n.n.n.n.b.n.n.n.n.c.G.M.N.G.n.c.c.n.n.c.z.z.z.z.z.z.z.z.z.z.zb5bUbU.l.lb5.l.l.l.db6.y.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.i.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.m.m.m.m.Vbzbzbz.Q.m.m.m.m.m.6bzbzbz.b.b.Mbzbzbzbzbzbz.6.G.b.b.Tbzbzbzbzbz#c.Q.n.n.n.n.n.c.c.c.c.c.c.c.c.c.c.z.z.z.z.z.z.z.z.z.l.l.y.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.i.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.m.m.Vbzbzbz.4.m.m.m.m.gbzbzbzbz.m.m.Mbzbz#c.9#cbzbz#c.7.b.X.9.X.X.4bzbzbz.r.n.n.n.n.n.n.c.c.c.c.c.c.c.c.c.c.z.z.z.z.z.z.z.z.z.o.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.i.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.Vbzbzbz#c.m.m.m.m.Tbzbzbzbz.m.m.Mbzbz.X.b.b.6bzbz.X.b.b.b.b.b.b.Tbzbz.X.n.n.n.n.n.n.n.n.c.c.c.c.c.c.c.c.c.z.z.z.z.z.z.z.z.o.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.i.#.#.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.Vbz##bzbz.T.m.m.m.6bz##bzbz.m.m.Mbzbz.V.m.b.Mbzbz.X.b.b.b.b.b.b.Qbzbz.T.n.n.n.n.n.n.n.n.n.c.c.c.c.c.c.c.c.c.c.z.z.z.z.z.z.W.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.i.#.#.#.#.#.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.Vbz.9.6bz.6.a.m.gbz.6.9bzbz.m.m.Mbzbz.V.m.m.Tbzbz.T.b.b.b.b.b.h##bz##.h.n.n.n.n.n.n.n.n.n.n.n.c.c.c.c.c.c.c.c.c.c.z.z.z.z#t.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.i.#.#.#.#.#.#.#.#.#.#.#.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.Vbz.9.Tbzbz.f.a.Tbz.T.9bzbz.m.m.Mbzbz.V.m.Q#cbz#c.h.b.b.T.9.9bz#c.4.h.b.b.b.n.n.n.n.n.n.n.n.n.n.c.c.c.c.c.c.c.c.c.c.z.z.z#t.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.h.#.#.#.#.#.#.#.#.#.#.#.#.#.#.a.a.a.a.a.a.a.a.a.a.a.a.Vbz.9.f#cbz.T.a.6bz.f.9bzbz.m.m.Mbzbzbzbzbzbz#c.T.m.m.b.Xbzbzbzbz.6.G.b.b.b.b.b.n.n.n.n.n.n.n.n.n.n.c.c.c.c.c.c.c.c.c.z.z#t.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.h.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.a.a.a.a.a.a.a.a.a.a.Vbz.9.a.4bz.9.fbz.6.a.9bzbz.m.m.Mbzbz#c.9.9.V.q.m.m.m.m.m.b.b.Q#cbz#c.7.b.b.b.b.b.b.n.n.n.n.n.n.n.n.n.n.c.c.c.c.c.c.c.c.c#t.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.h.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#b7.a.a.a.a.a.a.a.Vbz.9.a.Pbzbz.Vbz.T.a.9bzbz.a.m.Mbzbz.V.m.m.m.m.m.m.m.m.m.mb3.b.Mbzbz.4.b.b.b.b.b.b.b.b.n.n.n.n.n.n.n.n.n.c.c.c.c.c.c.c.c.x.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.h.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.a.a.a.a.Vbz.9.a.a#cbz#cbz.f.a.9bzbz.a.a.Mbzbz.V.m.m.m.m.m.m.m.m.m.m.m.m.mbzbz.9.b.b.b.b.b.b.b.b.b.n.n.n.n.n.n.n.n.n.c.c.c.c.c.c.c.x.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.h.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.a.a.Vbz.9.a.a.1bzbz.6.a.a.9bzbz.a.a.Mbzbz.V.m.m.m.m.m.m.m.m.m.m.m.m.Vbzbz.4.b.b.b.b.b.b.b.b.b.b.b.n.n.n.n.n.n.n.n.n.c.c.c.c.c#t.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.h.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.Vbz.9.a.a.Ebzbz.T.a.a.9bzbz.a.a.Mbzbz.V.a.m.m.m.m.m.m.6.9.V.V.4bzbz#c.qb2.b.b.b.b.b.b.b.b.b.b.b.n.n.n.n.n.n.n.n.n.c.c.c.c#t.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.h.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.Vbz.9.a.a.a.M.M.f.a.a.9bzbz.a.a.Mbzbz.V.a.a.a.m.m.m.m.4bzbzbzbzbz.9.F.m.mb1.b.b.b.b.b.b.b.b.b.b.b.n.n.n.n.n.n.n.n.n.n.c.c#t.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.h.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.m.m.m.g.M.M.M.g.m.m.m.m.m.mb4.b.b.b.b.b.b.b.b.b.b.b.n.n.n.n.n.n.n.n.n.c#t.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.i.u.Y.V.h.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.m.m.m.m.m.m.m.m.m.m.m.m.m.b.b.b.b.b.b.b.b.b.b.b.n.n.n.n.n.n.n.n.n#t.V.Y.u.i.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.z.h.t.Y.V.h.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.m.m.m.m.m.m.m.m.m.m.m.m.mb8.b.b.b.b.b.b.b.b.b.b.b.n.n.n.n.n.n.n#t.V.Y.t.h.z.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.c.h.s.N.U.h.8.8.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#b9.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.m.m.m.m.m.m.m.m.m.m.m.m.m.b.b.b.b.b.b.b.b.b.b.b.n.n.n.n.n.n#t.U.N.s.h.c.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQt.#.a.c.g.r.M.T.h.8.8.8.8.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.m.m.m.m.m.m.m.m.m.m.m.m.m.b.b.b.b.b.b.b.b.b.b.n.n.n.n.n.W.T.M.r.g.c.a.#QtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQt.#.c.f.q.J.R.h.8.8.8.8.8.8.8.#.8.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.m.m.m.m.m.m.m.m.m.m.m.m.m.b.b.b.b.b.b.b.b.b.b.n.n.n.n.W.R.J.q.f.c.#QtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQt.#.n.e.p.G.O.U.1.5.6.9#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#..9.6.5.1.U.O.G.p.e.n.#QtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQt.#.b.d.o.s.L.Q.U.X.1.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.4.1.X.U.Q.L.s.o.d.b.#QtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQt.#.m.c.f.x.B.L.O.R.T.U.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.V.U.T.R.O.L.B.x.f.c.m.#QtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQt.#.#.b.l.g.x.s.G.J.M.N.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.Y.N.M.J.G.s.x.g.l.b.#.#QtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQt.#.a.n.l.f.o.p.q.r.s.t.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.u.t.s.r.q.p.o.f.l.n.a.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.#.a.b.c.d.e.f.g.h.h.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.i.h.h.g.f.e.d.c.b.a.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.#.#.m.b.n.c.c.c.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.z.c.c.c.n.b.m.#.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt.#.#.#.#.#.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.#.#.#.#.#QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt"};


/* 
 *  Constructs a UzooMain which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
UzooMain::UzooMain( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    QPixmap image0( ( const char** ) image0_data );
    if ( !name )
	setName( "UzooMain" );
    resize( 266, 383 ); 
    setCaption( tr( "Sori Uzoo" ) );
    UzooMainLayout = new QVBoxLayout( this ); 
    UzooMainLayout->setSpacing( 0 );
    UzooMainLayout->setMargin( 0 );

    mainTabWidget = new QTabWidget( this, "mainTabWidget" );
    mainTabWidget->setTabPosition( QTabWidget::Top );
    mainTabWidget->setTabShape( QTabWidget::Rounded );

    tab = new QWidget( mainTabWidget, "tab" );
    tabLayout = new QVBoxLayout( tab ); 
    tabLayout->setSpacing( 5 );
    tabLayout->setMargin( 5 );

    Layout14 = new QHBoxLayout; 
    Layout14->setSpacing( 6 );
    Layout14->setMargin( 0 );

    searchLineEdit = new QLineEdit( tab, "searchLineEdit" );
    searchLineEdit->setMinimumSize( QSize( 0, 0 ) );
    Layout14->addWidget( searchLineEdit );

    searchPBtn = new QPushButton( tab, "searchPBtn" );
    searchPBtn->setEnabled( FALSE );
    searchPBtn->setMaximumSize( QSize( 70, 32767 ) );
    searchPBtn->setText( tr( "Search" ) );
    Layout14->addWidget( searchPBtn );

    stopPBtn = new QPushButton( tab, "stopPBtn" );
    stopPBtn->setEnabled( FALSE );
    stopPBtn->setMaximumSize( QSize( 70, 32767 ) );
    stopPBtn->setText( tr( "Stop" ) );
    Layout14->addWidget( stopPBtn );
    tabLayout->addLayout( Layout14 );

    searchTitle = new QLabel( tab, "searchTitle" );
    searchTitle->setMaximumSize( QSize( 32767, 20 ) );
    searchTitle->setFrameShape( QLabel::Box );
    searchTitle->setFrameShadow( QLabel::Raised );
    searchTitle->setText( tr( "title" ) );
    tabLayout->addWidget( searchTitle );

    searchListBox = new SearchListBox( tab, "searchListBox" );
    tabLayout->addWidget( searchListBox );

    Layout9 = new QVBoxLayout; 
    Layout9->setSpacing( 0 );
    Layout9->setMargin( 0 );

    Layout9_2 = new QHBoxLayout; 
    Layout9_2->setSpacing( 0 );
    Layout9_2->setMargin( 0 );

    searchSinger = new QLabel( tab, "searchSinger" );
    searchSinger->setMaximumSize( QSize( 32767, 20 ) );
    searchSinger->setFrameShape( QLabel::Box );
    searchSinger->setFrameShadow( QLabel::Raised );
    searchSinger->setText( tr( "singer" ) );
    Layout9_2->addWidget( searchSinger );

    searchQuality = new QLabel( tab, "searchQuality" );
    searchQuality->setMaximumSize( QSize( 32767, 20 ) );
    searchQuality->setFrameShape( QLabel::Box );
    searchQuality->setFrameShadow( QLabel::Raised );
    searchQuality->setText( tr( "quality" ) );
    Layout9_2->addWidget( searchQuality );
    Layout9->addLayout( Layout9_2 );

    Layout10 = new QHBoxLayout; 
    Layout10->setSpacing( 0 );
    Layout10->setMargin( 0 );

    searchDownLoad = new QLabel( tab, "searchDownLoad" );
    searchDownLoad->setMaximumSize( QSize( 32767, 20 ) );
    searchDownLoad->setFrameShape( QLabel::Box );
    searchDownLoad->setFrameShadow( QLabel::Raised );
    searchDownLoad->setText( tr( "percent" ) );
    Layout10->addWidget( searchDownLoad );

    searchSize = new QLabel( tab, "searchSize" );
    searchSize->setMaximumSize( QSize( 32767, 20 ) );
    searchSize->setFrameShape( QLabel::Box );
    searchSize->setFrameShadow( QLabel::Raised );
    searchSize->setText( tr( "size" ) );
    Layout10->addWidget( searchSize );
    Layout9->addLayout( Layout10 );

    Layout11 = new QHBoxLayout; 
    Layout11->setSpacing( 0 );
    Layout11->setMargin( 0 );

    searchUser = new QLabel( tab, "searchUser" );
    searchUser->setMaximumSize( QSize( 32767, 20 ) );
    searchUser->setFrameShape( QLabel::Box );
    searchUser->setFrameShadow( QLabel::Raised );
    searchUser->setText( tr( "user" ) );
    Layout11->addWidget( searchUser );

    searchTime = new QLabel( tab, "searchTime" );
    searchTime->setMaximumSize( QSize( 32767, 20 ) );
    searchTime->setFrameShape( QLabel::Box );
    searchTime->setFrameShadow( QLabel::Raised );
    searchTime->setText( tr( "time" ) );
    Layout11->addWidget( searchTime );
    Layout9->addLayout( Layout11 );
    tabLayout->addLayout( Layout9 );
    mainTabWidget->insertTab( tab, tr( "Search" ) );

    tab_2 = new QWidget( mainTabWidget, "tab_2" );
    tabLayout_2 = new QVBoxLayout( tab_2 ); 
    tabLayout_2->setSpacing( 5 );
    tabLayout_2->setMargin( 5 );

    TextLabel5 = new QLabel( tab_2, "TextLabel5" );
    TextLabel5->setMaximumSize( QSize( 32767, 25 ) );
    TextLabel5->setFrameShape( QLabel::Box );
    TextLabel5->setFrameShadow( QLabel::Raised );
    TextLabel5->setText( tr( "DownLoad" ) );
    tabLayout_2->addWidget( TextLabel5 );

    downloadListView = new ConditionListView( tab_2, "downloadListView" );
    tabLayout_2->addWidget( downloadListView );

    TextLabel6 = new QLabel( tab_2, "TextLabel6" );
    TextLabel6->setMaximumSize( QSize( 32767, 25 ) );
    TextLabel6->setFrameShape( QLabel::Box );
    TextLabel6->setFrameShadow( QLabel::Raised );
    TextLabel6->setText( tr( "UpLoad" ) );
    tabLayout_2->addWidget( TextLabel6 );

    uploadListView = new ConditionListView( tab_2, "uploadListView" );
    tabLayout_2->addWidget( uploadListView );
    mainTabWidget->insertTab( tab_2, tr( "DownUp" ) );

    tab_3 = new QWidget( mainTabWidget, "tab_3" );
    tabLayout_3 = new QVBoxLayout( tab_3 ); 
    tabLayout_3->setSpacing( 6 );
    tabLayout_3->setMargin( 11 );
    QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    tabLayout_3->addItem( spacer );

    configPBtn = new QPushButton( tab_3, "configPBtn" );
    configPBtn->setText( tr( "&Configure" ) );
    tabLayout_3->addWidget( configPBtn );

    helpPBtn = new QPushButton( tab_3, "helpPBtn" );
    helpPBtn->setText( tr( "Help && Infomation" ) );
    tabLayout_3->addWidget( helpPBtn );

    appearanceConfigPBtn = new QPushButton( tab_3, "appearanceConfigPBtn" );
    appearanceConfigPBtn->setEnabled( FALSE );
    appearanceConfigPBtn->setText( tr( "&Appearance Configure" ) );
    tabLayout_3->addWidget( appearanceConfigPBtn );
    QSpacerItem* spacer_2 = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    tabLayout_3->addItem( spacer_2 );
    mainTabWidget->insertTab( tab_3, tr( "Etc" ) );

    tab_4 = new QWidget( mainTabWidget, "tab_4" );
    tabLayout_4 = new QVBoxLayout( tab_4 ); 
    tabLayout_4->setSpacing( 6 );
    tabLayout_4->setMargin( 11 );

    printLabel = new QLabel( tab_4, "printLabel" );
    printLabel->setMaximumSize( QSize( 32767, 50 ) );
    printLabel->setFrameShape( QLabel::Box );
    printLabel->setFrameShadow( QLabel::Raised );
    printLabel->setText( tr( "http://sonegy.home.uos.ac.kr/soriuzoo" ) );
    printLabel->setAlignment( int( QLabel::AlignCenter ) );
    tabLayout_4->addWidget( printLabel );

    Layout4 = new QHBoxLayout; 
    Layout4->setSpacing( 6 );
    Layout4->setMargin( 0 );

    TextLabel1 = new QLabel( tab_4, "TextLabel1" );
    TextLabel1->setText( tr( "UserID" ) );
    Layout4->addWidget( TextLabel1 );
    QSpacerItem* spacer_3 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout4->addItem( spacer_3 );

    idLineEdit = new QLineEdit( tab_4, "idLineEdit" );
    Layout4->addWidget( idLineEdit );
    tabLayout_4->addLayout( Layout4 );

    Layout5 = new QHBoxLayout; 
    Layout5->setSpacing( 6 );
    Layout5->setMargin( 0 );

    TextLabel2_2 = new QLabel( tab_4, "TextLabel2_2" );
    TextLabel2_2->setText( tr( "PassWord" ) );
    Layout5->addWidget( TextLabel2_2 );
    QSpacerItem* spacer_4 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout5->addItem( spacer_4 );

    passwdLineEdit = new QLineEdit( tab_4, "passwdLineEdit" );
    passwdLineEdit->setEchoMode( QLineEdit::Password );
    Layout5->addWidget( passwdLineEdit );
    tabLayout_4->addLayout( Layout5 );

    Layout6 = new QHBoxLayout; 
    Layout6->setSpacing( 6 );
    Layout6->setMargin( 0 );

    connectPBtn = new QPushButton( tab_4, "connectPBtn" );
    connectPBtn->setText( tr( "Connect" ) );
    Layout6->addWidget( connectPBtn );
    tabLayout_4->addLayout( Layout6 );

    Line7 = new QFrame( tab_4, "Line7" );
    Line7->setFrameStyle( QFrame::HLine | QFrame::Sunken );
    tabLayout_4->addWidget( Line7 );

    UzooPixmap = new QLabel( tab_4, "UzooPixmap" );
    UzooPixmap->setPixmap( image0 );
    UzooPixmap->setScaledContents( FALSE );
    UzooPixmap->setAlignment( int( QLabel::AlignCenter ) );
    tabLayout_4->addWidget( UzooPixmap );
    mainTabWidget->insertTab( tab_4, tr( "Connect" ) );
    UzooMainLayout->addWidget( mainTabWidget );

    Layout10_2 = new QHBoxLayout; 
    Layout10_2->setSpacing( 0 );
    Layout10_2->setMargin( 0 );

    message0Label = new QLabel( this, "message0Label" );
    message0Label->setMaximumSize( QSize( 32767, 25 ) );
    message0Label->setFrameShape( QLabel::Box );
    message0Label->setFrameShadow( QLabel::Raised );
    message0Label->setText( tr( "" ) );
    Layout10_2->addWidget( message0Label );

    message1Label = new QLabel( this, "message1Label" );
    message1Label->setMaximumSize( QSize( 32767, 25 ) );
    message1Label->setFrameShape( QLabel::Box );
    message1Label->setFrameShadow( QLabel::Raised );
    message1Label->setText( tr( "" ) );
    Layout10_2->addWidget( message1Label );
    UzooMainLayout->addLayout( Layout10_2 );

    Line1 = new QFrame( this, "Line1" );
    Line1->setFrameStyle( QFrame::HLine | QFrame::Sunken );
    UzooMainLayout->addWidget( Line1 );

    // tab order
    setTabOrder( idLineEdit, passwdLineEdit );
    setTabOrder( passwdLineEdit, connectPBtn );
    setTabOrder( connectPBtn, searchLineEdit );
    setTabOrder( searchLineEdit, searchPBtn );
    setTabOrder( searchPBtn, stopPBtn );
    setTabOrder( stopPBtn, configPBtn );
    setTabOrder( configPBtn, appearanceConfigPBtn );
    setTabOrder( appearanceConfigPBtn, mainTabWidget );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
UzooMain::~UzooMain()
{
    // no need to delete child widgets, Qt does it all for us
}

