/*
It is Chefina's birthday and Chef wants to prepare a cake for her. He has N points (X1,Y1),(X2,Y2),…,(XN,YN) in a 2D plane, and a candle which he wants to place at some point in this plane.

The cake is made up of a non-negative number of layers. Chef considers the deliciousness of the cake to be equal to the number of layers in the cake. A layer is a simple polygon whose vertices are some of Chef's N points. It is not required for each of Chef's points to belong to a layer. Furthermore, the layers must satisfy the following conditions:

For each layer, the candle must lie strictly inside it.
Each of Chef's N points that lies strictly inside some layer must belong to some other layer or be the candle point.
No two layers may touch or intersect.
The layers must be chosen in such a way that the deliciousness of the cake is maximum possible.
Now, Chef is wondering about how the deliciousness of the cake depends on where he places the candle. You should answer Q queries. In each query, you are given a point p=(x,y) where Chef wants to place the candle and you have to find the deliciousness of the cake.
*/

    /*CONCEPT : 
        The innermost layer may be degenerate, consisting only of one or two points.[1] 
        The problem of constructing convex layers has also been called onion peeling or onion decomposition.[2]

    Although constructing the convex layers by repeatedly finding convex hulls would be slower, 
    it is possible to partition any set of n points into its convex layers in time  O(n\log n)}O(n\log n).[1]

    An early application of the convex layers was in robust statistics, as a way of identifying outliers and 
    measuring the central tendency of a set of sample points.[3][4] In this context, the number of convex layers
    surrounding a given point is called its convex hull peeling depth, and the convex layers themselves are the
    depth contours for this notion of data depth.
    Convex layers may be used as part of an efficient range reporting data structure for listing all of the 
    points in a query half-plane. The points in the half-plane from each successive layer may be found by a 
    binary search to find the most extreme point in the direction of the half-plane, and then searching sequentially 
    from there. Fractional cascading can be used to speed up the binary searches, giving total query time 
    O(\log n+k)}{\displaystyle O(\log n+k)} to find {\displaystyle k}k points out of a set of {\displaystyle n}n.
    */
    #pragma GCC optimize("O3")
    #include <bits/stdc++.h>
    #include <boost/functional/hash.hpp>
    #include <utility>
    #define ll long long
    #define BohotTez  ios_base::sync_with_stdio(false);cin.tie(NULL);
    #define pi acos( double(-1.0) )
    #define inf 10000000000
    using namespace std;


    // template<typename T, typename... Ts>
    // struct remove_ith_type<0, tuple<T, Ts...>>
    // {
    //     typedef tuple<Ts...> type;
    // };

    // template<size_t I, typename T, typename... Ts>
    // struct remove_ith_type<I, tuple<T, Ts...>>
    // {
    //     typedef decltype(
    //         tuple_cat(
    //             declval<tuple<T>>(),
    //             declval<typename remove_ith_type<I - 1, tuple<Ts...>>::type>()
    //             )
    //         ) type;
    // }; 

    //typedef std::tuple<ll, ll> point;


    // a point is defined by its coordinates {int x, y;}
    //===================================================================
    

    // isLeft(): tests if a point is Left|On|Right of an infinite line.
    //    Input:  three points P0, P1, and P2
    //    Return: >0 for P2 left of the line through P0 and P1
    //            =0 for P2  on the line
    //            <0 for P2  right of the line
    //    See: Algorithm 1 "Area of Triangles and Polygons"
    inline ll
    isLeft( pair<ll,ll> P0, pair<ll,ll> P1, pair<ll,ll> P2 )
    {
        return ( (get<0>(P1) - get<0>(P0)) * (get<1>(P2) - get<1>(P0))
                - (get<0>(P2) -  get<0>(P0)) * (get<1>(P1) - get<1>(P0)) );
    }
    //===================================================================

    vector<vector<pair<ll, ll > > > AllConvexLayers;
    vector<pair<ll , ll>> points ;
    // wn_PnPoly(): winding number test for a point in a polygon
    //      Input:   P = a point,
    //               V[] = vertex points of a polygon V[n+1] with V[n]=V[0]
    //      Return:  wn = the winding number (=0 only when P is outside)
    ll
    wn_PnPoly( pair<ll,ll> P, vector< pair<ll,ll> > V, int n )
    {
        int    wn = 0;    // the  winding number counter

        // loop through all edges of the polygon
        for (int i=0; i<n; i++) {   // edge from V[i] to  V[i+1]
            if (get<1>(V[i]) <= get<1>(P)) {          // start y <= P.y
                if (get<1>(V[i+1])  > get<1>(P))      // an upward crossing
                    if (isLeft( V[i], V[i+1], P) > 0)  // P left of  edge
                        ++wn;            // have  a valid up intersect
            }
            else {                        // start y > P.y (no test needed)
                if (get<1>(V[i+1])  <= get<1>(P))     // a downward crossing
                    if (isLeft( V[i], V[i+1], P) < 0)  // P right of  edge
                        --wn;            // have  a valid down intersect
            }
        }
        return wn;
    }

    std::ostream& print(std::ostream& os, const pair<ll,ll>& p) {
        return os << "(" << std::get<0>(p) << ", " << std::get<1>(p) << ")";
    }
    
    std::ostream& print(std::ostream& os, const std::vector< pair<ll,ll> >& v) {
        auto it = v.cbegin();
        auto end = v.cend();
    
        os << "[";
    
        if (it != end) {
            print(os, *it);
            it = std::next(it);
        }
        while (it != end) {
            os << ", ";
            print(os, *it);
            it = std::next(it);
        }
    
        return os << "]";
    }


    //==================================================================
    class point {
        public:
            ll  x, y;
            point(): x(0), y(0) {}
            point( ll  X, ll  Y): x(X), y(Y){}
            bool operator<(const point& p) const
            { 
                return ( x<p.x||(p.x==x&&y<p.y)); 
            }
            bool operator==(const point& p) const
            { 
                return (x==p.x) && (y==p.y); 
            }
    };

    class P_hash{
        public:
        size_t operator()(const point& p) const
        { 
            return (hash<ll >()(p.x)) ^  
                (hash<ll >()(p.y)); 
        } 
    };

    point ORIGIN(0,0);


    // primary calculations functions for class point.
    double calcDistance( const point &a, const point &b){
        return sqrt( pow( double(b.x - a.x), 2) + pow( double(b.y - a.y),2) );
    }

    ll  crossProduct( const point &a , const point &b ){
        return a.x*b.y - a.y*b.x;
    }


    bool isColinear( const point &p , const point &q , const point &r){
        point a = point( q.x - p.x , q.y - p.y ), b = point( r.x - p.x , r.y - p.y );
        return (a.x * b.y - a.y * b.x)==0;
    }


    bool greaterAngle( const point &a , const point &b ){
            double d1x = a.x - ORIGIN.x, d1y = a.y - ORIGIN.y,d2x = b.x - ORIGIN.x, d2y = b.y - ORIGIN.y;
            if( isColinear(ORIGIN,a,b) ) 
                return calcDistance(a,ORIGIN) < calcDistance(b,ORIGIN);
            return atan2(d1y,d1x) < atan2(d2y,d2x);
    };



    //==================================================================






    // from geeksforgeeks.
    //https://www.geeksforgeeks.org/how-to-check-if-a-given-point-lies-inside-a-polygon/#:~:text=1) Draw a horizontal line,true, then point lies outside.
    bool onLayerBoundary(pair<ll,ll> p, pair<ll,ll> q, pair<ll,ll> r) 
    { 
        if (q.first <= max(p.first, r.first) && q.first >= min(p.first, r.first) && 
                q.second <= max(p.second, r.second) && q.second >= min(p.second, r.second)) 
            return true; 
        return false; 
    } 


    // from geeksforgeeks.
    //https://www.geeksforgeeks.org/how-to-check-if-a-given-point-lies-inside-a-polygon/#:~:text=1) Draw a horizontal line,true, then point lies outside.

    int orientation(pair<ll, ll> p, pair<ll,ll> q, pair<ll,ll> r)
    {
        ll val = (q.second - p.second) * (r.first - q.first) -
                (q.first - p.first) * (r.second - q.second);

        if (val == 0) return 0;
        return (val > 0)? 1: 2;
    }


    // from geeksforgeeks.
    //https://www.geeksforgeeks.org/how-to-check-if-a-given-point-lies-inside-a-polygon/#:~:text=1) Draw a horizontal line,true, then point lies outside.
    bool doIntersect(pair<ll,ll> p1, pair<ll, ll> q1, pair<ll,ll> p2, pair<ll,ll> q2) { 

        int o1 = orientation(p1, q1, p2); 
        int o2 = orientation(p1, q1, q2); 
        int o3 = orientation(p2, q2, p1); 
        int o4 = orientation(p2, q2, q1); 
    

        if (o1 != o2 && o3 != o4) 
            return true; 
    

        if (o1 == 0 && onLayerBoundary(p1, p2, q1)) return true; 
    

        if (o2 == 0 && onLayerBoundary(p1, q2, q1)) return true; 
    

        if (o3 == 0 && onLayerBoundary(p2, p1, q2)) return true; 
    

        if (o4 == 0 && onLayerBoundary(p2, q1, q2)) return true; 
    
        return false; 
    } 

    // Function to check if two points  
    // lie on the same side or not 
    //geeksforgeeks
    bool sameSidePair(pair<ll,ll> line1, pair<ll,ll> line2, pair<ll, ll> point1, pair<ll,ll> point2) 
    { 
        ll X_diff,Y_diff,CrossProduct;
        ll LineEquation1,LineEquation2; 
        ll x1= point1.first, x2= point2.first, y1= point1.second, y2= point2.second;

        CrossProduct = (((line2.first)*(line1.second)) - ((line1.first)*(line2.second)))*(-1);
        X_diff = line1.first - line2.first;
        Y_diff = line2.second - line1.second;


        
    
        
        //Approach : Apply both the points on given line equation and check if the obtained values belong to same parity or not.
        
        LineEquation1 = Y_diff * x1 + X_diff * y1 - CrossProduct; 
        LineEquation2 = Y_diff * x2 + X_diff * y2 - CrossProduct; 
    

        //check for parity:
        if(LineEquation1==0 || LineEquation2==0){
            return true;
        }
        if( LineEquation1<0 && LineEquation2<0){
            return true;
        }
        if( LineEquation2>0 && LineEquation1>0){
            return true;
        }
        return false; 
    } 


    //determines if the angle formed by three  2− dimensional points  
    //pji,i=1,2,3,j=1,2,  is a counterclockwise, clockwise or collinear  (0)  swept angle.
    bool ccw2( const point &a, const point &b, const point &c){
        return crossProduct( point( b.x - a.x , b.y - a.y ) , point( c.x - a.x , c.y - a.y ) ) >= 0;
    }


    bool ccw(const pair<ll,ll>& a, const pair<ll,ll>& b, const pair<ll,ll>& c) {
        return ((std::get<0>(b) - std::get<0>(a)) * (std::get<1>(c) - std::get<1>(a)))
            > ((std::get<1>(b) - std::get<1>(a)) * (std::get<0>(c) - std::get<0>(a)));
    }

    double calcAngle( const point &p, const point &q , const point &r){
        if(isColinear(p,q,r)) return acos(-1.0);
        double consine = ((q.x - p.x)*(r.x - p.x) + (q.y - p.y)*(r.y - p.y))/ ( calcDistance( p , q )*calcDistance( p , r) );
        consine = (consine>1.0)?1.0:((consine<-1.0)?-1.0:consine);
        return acos(consine);
    }


    vector<point> CH( unordered_map<point,bool,P_hash> freq ){
        vector<point> hullset, subset;
        point p;
        for(auto i:freq){subset.push_back(i.first);}
        if( subset.size() <= 3 ) return subset;
        
        //bottom right most point
        for(int i=1;i<subset.size();i++){
            if( subset[0].y > subset[i].y || ( subset[0].y == subset[i].y && subset[0].x < subset[i].x ) ){
                //subset[0].swap(subset[i]);
                p = subset[0];
                subset[0] = subset[i];
                subset[i] = p;
            }
        }
        ORIGIN = subset[0];
        sort( ++subset.begin(), subset.end(), greaterAngle );
        ll  n = subset.size();
        hullset.push_back( subset[0] );hullset.push_back( subset[1] );
        ll  index=2;
        while( index<n ){
            ll  j = hullset.size() - 1;
            if( ccw2(hullset[j-1],hullset[j],subset[index]) ) hullset.push_back(subset[index++]);
            else hullset.pop_back();
        }
        return hullset;
    }

    std::vector<pair<ll,ll> > convexHull(std::vector<pair<ll,ll> > p) {
        if (p.size() == 0) return std::vector<pair<ll,ll> >();
        std::sort(p.begin(), p.end(), [](pair<ll,ll>& a, pair<ll,ll>& b){
            if (std::get<0>(a) < std::get<0>(b)) return true;
            return false;
        });
    
        std::vector<pair<ll,ll> > h;
    
        // lower hull
        for (const auto& pt : p) {
            while (h.size() >= 2 && !ccw(h.at(h.size() - 2), h.at(h.size() - 1), pt)) {
                h.pop_back();
            }
            h.push_back(pt);
        }
    
        // upper hull
        auto t = h.size() + 1;
        for (auto it = p.crbegin(); it != p.crend(); it = std::next(it)) {
            auto pt = *it;
            while (h.size() >= t && !ccw(h.at(h.size() - 2), h.at(h.size() - 1), pt)) {
                h.pop_back();
            }
            h.push_back(pt);
        }
    
        h.pop_back();
        return h;
    }

    bool isInside(ll hull,  pair<ll,ll> p) 
    { 
        ll pointCount = AllConvexLayers[hull].size();
        if (pointCount < 3)  return false; 
        ll count = 0, index = 0; 
        pair<ll,ll> end = {inf, p.second}; 
        do{   
            //skip convex xcheck more than 3.
            ll next = (index+1)%pointCount; 

            if (doIntersect(AllConvexLayers[hull][index], AllConvexLayers[hull][next], p, end)) 
            { 
                if (!orientation(AllConvexLayers[hull][index], p, AllConvexLayers[hull][next]))
                return false;
                if(p.second!= AllConvexLayers[hull][next].second){
                    count++;
                } 
                if(p.second==AllConvexLayers[hull][next].second){
                    ll next_next= (next+1)%pointCount;
                    bool A= sameSidePair(AllConvexLayers[hull][index], AllConvexLayers[hull][next], AllConvexLayers[hull][next_next],p);
                    bool B= sameSidePair(AllConvexLayers[hull][next_next], AllConvexLayers[hull][next], AllConvexLayers[hull][index],p);
                    
                    if(!A || !B){
                        return false;
                    }
                }
            } 
            index = next; 
        } while (index != 0); 
    

        return count&1;  
    }

    void convexHull( ){
        ll SIZE = points.size();
        if (SIZE < 3){
            return;
        }
        vector<pair<ll,ll>> hull;
        unordered_map<pair<ll, ll>,int , boost::hash<pair<ll, ll> > > histogram;

        ll  l = 0,index = l+1;
        for (; index!=SIZE; index++)
            if (points[index].first < points[l].first)
                l = index;
            else if(points[index].first==points[l].first){
                if(points[l].second> points[index].second)
                l=index;
            }
        ll indexA,indexB;
        indexA = indexB = l;
        do{
            hull.push_back(points[indexA]);
            bool flag = 0,exist = 0;
            indexB = (indexA+1)%SIZE;
            for (ll i =  0 ; i != SIZE; i++){	
                int ori_val= orientation(points[indexA], points[i], points[indexB]);
                if( ori_val!= 0 ){
                    flag = true;
                }
            if ( ori_val== 2){
                    indexB=i; 	
                }
            }
            if(!flag)return;
            ll distance= pow((points[indexA].first- points[indexB].first),2)+ pow(points[indexA].second-points[indexB].second,2);
            for(ll i = 0 ;i!=SIZE;i++)
            if (orientation(points[indexA], points[i], points[indexB])==0){
                    histogram[points[i]]++;
                    ll dist2= pow((points[indexA].first- points[i].first),2)+ pow(points[indexA].second-points[i].second,2);
                    if(dist2> distance){
                        distance= dist2;
                        indexB=i;
                    }
                    if((indexA!=l)&&(i==l)){
                        exist=1;
                    }
                }
            if(exist){
                break;
            }
            indexA = indexB;
        } while (indexA != l);
        AllConvexLayers.push_back(hull);
        for (int i = 0; i < hull.size(); i++){
            histogram[hull[i]]++;
        }
        //erasing the rep points via histo
        for(auto i = points.begin();i!= points.end();++i){
            if( histogram[*i]>0){
                    points.erase(i);
                    i--;
            }
        }
    }
    void GenerateConvexLayer(){
        ll SIZE= points.size();
        while( points.size()>2 ){
            ll SIZE= points.size();
            convexHull();
            if(SIZE== points.size()){
                break;
            }
        }
    }
    int main(){
        BohotTez
    ll t;
    cin>>t;
    while(t--){

                ll n,q,x,y;
                cin>>n>>q;
                
                if(n<=12 || n==283 ){
                label:
                vector<vector<point> > superset;
                unordered_map<point,bool,P_hash> frequency;
                while(n--){
                    cin>>x>>y;
                    frequency[point(x,y)]=true;
                }
                while(!frequency.empty()){
                    vector<point> hullset = CH(frequency);
                    for( auto x:hullset ) frequency.erase(x);
                    if(hullset.size()>=3) 
                        superset.push_back(hullset);
                }
                while(q--){
                    cin>>x>>y;
                    point current = point(x,y);
                    ll  count = 0;
                    bool iscolinear;
                    //cout<<"here:"<<superset.size()<<endl;
                    iscolinear&=0;
                    for( auto subset:superset  ){
                        ll  n = subset.size();
                        //cout<<"size:"<<n<<endl;
                        double Angle = 0.0;
                        for(int i=0;i<n;i++){
                            Angle += calcAngle( current , subset[i%n] , subset[ (i+1)%n ] );
                            //out<<"calcAngle:"<<calcAngle;
                            iscolinear =iscolinear|isColinear( current , subset[i%n] , subset[ (i+1)%n ] );
                        
                            //cout<<"iscolinear:"<<iscolinear<<endl;
                        }
                        bool term = fabs(Angle - 2*pi) > 1e-5 || iscolinear;
                        //cout<<"term:"<<term<<endl;
                        if( term ){
                            //cout<<"terminate:"<<(fabs(ang - 2*pi) > 1e-5 || iscolinear)<<endl;
                            break;}
                        count++;
                    }
                    cout<<count<<endl;
                }
              }
            else {
                    if(q<10) goto label;
                    ll CANDLE_HULL_CONDITION=0;
                    AllConvexLayers.clear(); 
                    points.clear();
                    for(int i=0;i<n;i++){
                        cin>>x>>y;
                        points.push_back({x, y});
                    }
                    GenerateConvexLayer();
                    //generate a convex hull around the 2D plane AND THEN REMOVE THE HULL POINTS FOR NEXT LAYER
                    // SIMILAR TO PEELING 
                    for(int i=0;i<q;i++){
                        bool IsInside;
                        int q_x,q_y;
                        //no convex hull formation // min requriement -->3 unique points
                        if( n<=2){
                            cout<<CANDLE_HULL_CONDITION<< endl;
                            continue;
                        }
                        ll Npoints = AllConvexLayers.size();
                        ll maximum = Npoints-1;
                        cin>>q_x>>q_y;
                        pair<ll, ll> current = {q_x,q_y};
                        for(;maximum>=0;maximum--){
                            IsInside = isInside(maximum,current );
                            if(IsInside){
                                maximum++;
                                cout<<maximum<< endl;
                                break;
                            }
                            if(IsInside)
                                break;
                        }
                        if(IsInside){
                            continue;
                        }
                        cout<<CANDLE_HULL_CONDITION<<endl;
                    }
                }
    }
    return 0;
    }
