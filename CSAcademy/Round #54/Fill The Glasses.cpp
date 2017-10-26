#include <bits/stdc++.h>

using namespace std;

int ar[105];
int main() {
    int a, b;
    cin >> a >> b;
    for(int i = 0;i < a; ++i){
        scanf("%d", &ar[i]);
    }
    sort(ar,ar + a);
    int tot = 0;
    for(int i = 0;i < b; ++i) tot+=ar[i];
    printf("%d\n", (tot + 99) / 100);
    return 0;
}
