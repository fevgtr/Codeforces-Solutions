#include <bits/stdc++.h>
#define rg register
#define il inline
using namespace std;
inline int read()
{
    register int x=0;
    register bool f=0;
    register char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-') f=1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+c-48;
        c=getchar();
    }
    return f?-x:x;
}
char cr[200];int tt;
inline void print(register int x,register char k='\n') {
    if(!x) putchar('0');
    if(x < 0) putchar('-'),x=-x;
    while(x) cr[++tt]=x%10+'0',x/=10;
    while(tt) putchar(cr[tt--]);
    putchar(k);
}
const int maxn=500050;
struct node{
    int l,r,opt,x;
}q[maxn];
int ans[maxn],n,m,fa[maxn],rt[maxn],cnt[maxn],d[maxn];
int L[maxn],R[maxn],lsh[maxn],tot,a[maxn],bl;
int mx,tag,l,r,tmp,ql,qr,x;
il int find(rg int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}
il void merge(rg int x,rg int y){
    if(rt[y]){
        fa[rt[x]]=rt[y];
    }
    else{
        rt[y]=rt[x];    
        lsh[rt[y]]=y;
    }
    cnt[y]+=cnt[x];
    rt[x]=cnt[x]=0;
}
il void build(){
    mx=tag=tot=0;
    memset(rt,0,sizeof(rt));
    memset(cnt,0,sizeof(cnt));
    for(rg int i=l;i<=r;i++){
        mx=max(mx,a[i]);
        if(rt[a[i]])fa[i]=rt[a[i]];
        else{
            rt[a[i]]=fa[i]=i;
            lsh[i]=a[i];
        }
        cnt[a[i]]++;
    }
}
il void modify()
{
    if((x<<1)<=mx-tag){
        for(int j=tag+1;j<=tag+x;j++) 
            if(rt[j]) merge(j,j+x);
        tag+=x;
    }
    else{
        for(int j=mx;j>tag+x;j--) 
            if(rt[j]) merge(j,j-x);
        if(tag+x<mx) mx=tag+x;
    }
}
void rebuild()
{
    for(rg int j=l;j<=r;j++){
        a[j]=lsh[find(j)];
        rt[a[j]]=cnt[a[j]]=0;
        a[j]-=tag;
    }
    for(int j=l-10;j<=r+10;j++) lsh[j]=0;
    tag=mx=tot=0;
    tmp=min(qr,r);
    for(rg int j=max(ql,l);j<=tmp;j++){
        a[j]=a[j]>x?a[j]-x:a[j];
    }
    for(rg int j=l;j<=r;j++){
        mx=max(mx,a[j]);
        if(rt[a[j]])fa[j]=rt[a[j]];
        else{
            rt[a[j]]=fa[j]=j;
            lsh[j]=a[j];
        }
        cnt[a[j]]++;
    }
}
void get(rg int i){
    if(x+tag>500000) return;
    if(ql<=l&&r<=qr) ans[i]+=cnt[x+tag];
    else{
        tmp=min(r,qr);
        for(int j=max(l,ql);j<=tmp;j++)
            if(lsh[find(j)]==tag+x) ans[i]++;
    }
}
signed main(){
    n=read();m=read();bl=sqrt(n-1)+1;
    for(rg int i=1;i<=n;i++){
        a[i]=read();
    }
    for(rg int i=1;i<=m;i++){
        q[i].opt=read();
        q[i].l=read();
        q[i].r=read();
        q[i].x=read();
    }
    int lxl=1;
    L[1]=1;
    while(L[lxl]+bl<n){
        R[lxl]=L[lxl]+bl-1;
        lxl++;
        L[lxl]=R[lxl-1]+1;
    }
    R[lxl]=n;
    for(rg int srz=1;srz<=lxl;srz++){
        l=L[srz],r=R[srz];
        build();
        for(rg int i=1;i<=m;i++){
            ql=q[i].l,qr=q[i].r,x=q[i].x;
            if(r<ql||qr<l) continue;
            if(q[i].opt^2){
                if(ql<=l&&r<=qr){
                    modify();
                }
                else{
                    rebuild();
                }
            }
            else{
                get(i);
            }
        }
    }
    for(rg int i=1;i<=m;i++) 
        if(q[i].opt==2) print(ans[i]);
    return 0;
}
