// Verified : AOJ 1238

class UnionFind {
private:
  vector<int> par;
public:

  void init(int _size){
    par.clear();
    par.resize(_size);
    rep(i,_size) par[i] = i;
  }
  
  int find(int x) {
    if( x == par[x] ) return x;
    return par[x] = find(par[x]);
  }

  void unit(int x,int y){
    x = find(x), y = find(y);
    if( x != y ) par[x] = y;
  }

};

struct Edge {
  int to;
  char type;
};

/*
  引数のグラフ内に複数の成分がまとめてはいっている場合、それらをそれぞれに分解して新たにvectorに詰め直して返す
 */
vector<vector<vector<Edge> > > split_graph(vector<vector<Edge> > &G,vector<vector<int> > &ori){
  UnionFind uf;
  uf.init(G.size());
  rep(i,G.size()) rep(j,G[i].size()) uf.unit(i,G[i][j].to);
  int dex = 0;
  map<int,int> mp;
  rep(i,G.size()) if( !mp.count(uf.find(i)) ) mp[uf.find(i)] = dex++;
  int V = mp.size();
  vector<vector<vector<Edge> > > ret(V);
  vector<int> SIZES(V,0);
  rep(i,G.size()) ++SIZES[mp[uf.find(i)]];
  rep(i,V) ret[i].resize(SIZES[i],vector<Edge>());
  vector<int> Index(G.size(),0);
  vector<int> vec_dex(V,0);
  rep(i,G.size()) Index[i] = vec_dex[mp[uf.find(i)]]++;

  // if you need
  ori.clear();
  ori.resize(V);
  rep(i,V) ori[i].resize(SIZES[i],-1);
  rep(i,G.size()) ori[mp[uf.find(i)]][Index[i]] = i;
  //

  rep(i,G.size()) rep(j,G[i].size()){
    assert( uf.find(i) == uf.find(G[i][j].to) );
    int group = mp[uf.find(i)];
    ret[group][Index[i]].push_back((Edge){Index[G[i][j].to],G[i][j].type}); // modify
  }
  return ret;
}
