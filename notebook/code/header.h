/* vimrc
set number
set sw=4
set ts=4
set softtabstop=4
set background=dark
map <C-n> :tabnext<Return>
map <C-p> :tabprev<Return>
map <Space> :nohl<Return>
set expandtab
set noincsearch
filetype indent on
set autowrite
au FileType cpp set makeprg=g++\ -O2\ -g\ -o\ %<\ %\ -Wall\ -Wextra */

#include <algorithm>
#include <cassert>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

typedef long long LL;
typedef long double LD;
typedef vector<int> VI;
typedef pair<int,int> PII;

#define REP(i,n) for(int i=0;i<(n);++i)
#define SIZE(c) ((int)((c).size()))
#define FOR(i,a,b) for (int i=(a); i<(b); ++i)
#define FOREACH(i,x) for (__typeof((x).begin()) i=(x).begin(); i!=(x).end(); ++i)
#define FORD(i,a,b) for (int i=((int)(a))-1; i>=(b); --i)
#define ALL(u) (u).begin(),(u).end()

#define pb push_back
#define mp make_pair
#define st first
#define nd second
