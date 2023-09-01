#include<bits/stdc++.h>

#define inf 100000000
#define int long long
#define ll long long
#define fr(a, b) for(int i = a; i < b; i++)
#define endl "\n"
#define mod 1000000007
#define pb push_back
#define vi vector<int>
#define read(x) int x; cin >> x
#define pi pair <int, int>

using namespace std;

int dist[100001];
bool spset[100001];
vi par (100001, -1);
vi vec;
vector<pi>adj[1000];

int Dijakstra(int n, int start, int end)
{
    priority_queue< pi , vector<pi>, greater<pi> > q;
    q.push({0, start});
    while(!q.empty())
    {
        pi p = q.top();
        int idx = q.top().second;
        q.pop();
        spset[idx] = 1;

        if (p.second == end){
            return p.first;
        }
        
        fr(0, adj[idx].size())
        {
            int v = adj[idx][i].first;
            int w = adj[idx][i].second;
            if ((!spset[v])&&dist[idx]!=INT_MAX&&dist[idx] + w<dist[v])
            {
                dist[v] = dist[idx] + w;
                par[v] = idx;
                q.push({dist[v], v});
            }
        }
    }
}

int maxi (int a[], int n)
{
    int ma = 0;
    int idx;

    fr(0, n){
        if(a[i] > ma){
            ma = a[i];
            idx = i;
        }
    }

    return idx;
}

signed main()
{
    cout << "IMPLEMENTATION OF PRIORITY SCHEDULING ALGORITHM" << endl;

    int bt[100], tat[100], wt[100], ct[100], pri[100],  
    cppri[100], dl[100], size[100], utility[100],
    traffic[100],  prisum[100], totalsum = 0;

    int n;  // number of roads
    int flag = 0;
    int x, copybt[20];
    int SUMTAT = 0, SUMWT = 0;
    int path[20];
    
    cout << "ENTER THE NUMBER OF ROADS: ";
    cin >> n;
    cout << endl;
    
    fr(0, n)
    {
        cout << "Enter The Values For Road-" << " : " << i + 1 << endl;
        cout << "FORMATION OF STRUCTURE OF MAP->" << endl;

        int node;   //number of cities
        int edge;   //number of routes
        int end2, end1, weight, END, ans;
        int start;

        cout << "ENTER NUMBER OF CITIES: ";
        cin >> node;
        cout << "ENTER NUMBER OF ROUTES: ";
        cin >> edge;

        fr(0, edge){
            cout << "ENTER THE ROUTE NUMBER " << i + 1 << " CITY <space> CITY <space> DISTANCE IN KM: ";
            int city1, city2, d;
            cin >> city1 >> city2 >> d;
            adj[city1].pb({city2, d});
            adj[city2].pb({city1, d});
        }

        cout << "MAP FORMED SUCCESSFULLY" << endl;
        cout << "ENTER THE START CITY FROM WHERE THE MINIMUM DISTANCE SHOULD BE FOUND: ";
        cin >> start;
        cout << "ENTER THE DESTINATION CITY TO WHICH THE MINIMUM DISTANCE SHOULD BE FOUND : ";
        cin >> END;

        fr(1, node + 1)
        {
            dist[i] = INT_MAX;
            spset[i] = 0;
        }

        dist[start] = 0;
        par[start] = -1;

        ans = Dijakstra(node, start, END);
        
        cout << "SHORTEST PATH BETWEEN SOURCE AND DESTINATION CITY BY DIJKSTRA'S ALGORITHM-> " << ans << endl;
        size[i] = ans;
        cout << "SHORTEST PATH FOLLOWED IS: ";
        vec.pb(END);
        int idx = END;
        
        while (par[idx] != -1)
        {
            vec.pb(par[idx]);
            idx = par[idx];
        }
        
        for(int i = vec.size()-1; i >=  0; i--)
            cout << vec[i] << " ";

        cout << endl;
        par.clear();
        vec.clear();
        
        fr(0, node + 1) 
            adj[i].clear();
        
        cout << "\nEnter Utility Of The Road(In days): ";
        cin >> utility[i];
        cout << "Enter Traffic Of The Road(In days): ";
        cin >> traffic[i];
        cout << "Enter Estimated Finish Time For Road(In days): ";
        cin >> bt[i];
        cout << "Enter The Dead Line For Road(In days): ";
        cin >> dl[i];
        cout << endl;
    }

    fr(0, n){
        prisum[i] = size[i] + utility[i] + traffic[i];
        totalsum +=  prisum[i];
    }

    fr(0, n){
        pri[i] = (prisum[i]*100)/totalsum;
    }

    fr(0, n){
        for(int j = 0; j < n; j++){
            if(i!=j){
                if(pri[i] == pri[j]){
                    if(utility[i] > utility[j]){
                        ++pri[i];
                    }
                    else if(utility[j] > utility[i]){
                        ++pri[j];
                    }
                    else if(traffic[i] > traffic[j]){
                        ++pri[i];
                    }
                    else if(traffic[j] > traffic[i]){
                        ++pri[j];
                    }
                    else if(size[i] > size[j]){
                        ++pri[i];
                    }
                    else if(size[j] > size[i]){
                        ++pri[j];
                    }
                    else{
                        ++pri[i];
                    }
                }
            }
        }
    }

    cout << "THE OBTAINED PRIORITIES ARE:\n" << endl;

    fr(0, n)
        cout << "Priority of Road " << i + 1 << " =  " << pri[i] << endl;

    fr(0, n)
        cppri[i] = pri[i];
        
    for(int k = 0; k < n; k++)
    {
        x = maxi(pri, n);
        SUMWT += bt[x];
        ct[x] = SUMWT;
        pri[x] = -1;
    }

    fr(0, n){
        wt[i] = ct[i]-bt[i];
    }

    cout << "ROAD" << "\t" << "PRIORITY_OBTAINED    ESTIMATED TIME   WAITING TIME   TOTAL TIME" << endl << endl;
    
    fr(0, n)
    {
    printf("Road %d\t  %d             \t%d days   \t%d days       %d days\n", i + 1, cppri[i], bt[i], wt[i], ct[i]);
    }

    SUMTAT = 0;
    SUMWT = 0;

    fr(0, n){
        SUMTAT = SUMTAT + ct[i];
        SUMWT = SUMWT + wt[i];
    }

    cout << endl << endl << "Average TURNAROUND TIME = " << SUMTAT/n << " days" << endl;
    cout << endl << "Average WAITING TIME = " << SUMWT/n << " days" << endl << endl << endl;
    
    fr(0, n){
        if(dl[i] < ct[i]){
            flag = 1;
            break;
        }
    }

    if(!flag){
        cout << "NO PROBLEMS WITH THE SEQUENCE:" << endl;
    }
    else{

       cout << "DEADLINE NEEDS TO BE COMPROMISED" << endl << endl;
    
    for(int i = 0; i < n; i++){
        x = maxi(cppri, n);
        cout << "Road " << x + 1 << ",  ";
        cppri[x] = -1;
    }
    
    cout << endl << endl;
    
    cout << "IMPLEMENTATION OF BANKER'S ALGORITHM" << endl;
    int  m,  i,  j,  k;
    cout << endl << "ENTER NUMBER OF ROADS: ";
    cin >> n;
    cout << endl << "ENTER NUMBER OF RESOURCES: ";
    cin >> m;
    int alloc[n][m];
    cout << endl << "ENTER VALUES FOR ALLOCATION MATRIX: ";
    
    fr(0, n){
        cout << endl << "ENTER VALUES OF ALLOCATION FOR ROAD R" << i << " : ";
        for(int j = 0; j < m; j++){
            cin >> alloc[i][j];
        }
    }

    int max[n][m] ;
    cout << endl << "ENTER VALUES FOR MAXIMUM NEED MATRIX:" << endl;
    
    fr(0, n){
        cout << endl << "ENTER VALUES OF MAXIMUM NEED FOR ROAD R" << i << ": ";
        for(int j = 0; j < m; j++){
            cin >> max[i][j];
        }
    }

    int avail[m] ;
    cout << endl << "ENTER VALUES FOR AVAILABILITY: ";
    
    for(int i = 0; i < m; i++){
            cin >> avail[i];
    }

    int f[n], ans[n], ind = 0;
    for(k = 0; k < n; k++) {
        f[k] = 0;
    }

    int need[n][m];
    fr(0, n){
        for(j = 0; j < m; j++)
            need[i][j] = max[i][j]-alloc[i][j];
    }

    cout << endl << "NEED MATRIX:" << endl;
    fr(0, n){
        for(j = 0; j < m; j++){
            cout << need[i][j] << "  ";}
        cout << endl;
    }

    int y = 0;
    for(k = 0; k < n; k++){
        for(i = 0; i < n; i++){
            if(f[i] == 0){
                int flag = 0;
                for(j = 0; j < m; j++){
                    if(need[i][j] > avail[j]){
                        flag = 1;
                        break;
                    }
                }

                if(flag == 0){
                    ans[ind++] = i;
                    cout << endl << "R" << i << " is allocated" << endl;
                    cout << endl << "Availability is: ";
                    for (y = 0; y < m; y++){
                        avail[y] +=  alloc[i][y];
                        cout << avail[y] << ", ";
                    }
                    cout << endl;
                    f[i] = 1;
                }
            }
        }
    }
    
    if(ind == n){
        cout << endl << "SAFE Sequence Exists Which Is: " << endl;
        fr(0, n - 1)
            cout << " R" << ans[i] << " ->";
        cout << " R" << ans[n-1] << endl;
    }
    else
        cout << "SAFE Sequence Does Not Exist" << endl;
    
    }
    return 0;
}