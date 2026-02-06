#include<iostream>
#include<algorithm>
#include<vector>
#include<iomanip>
using namespace std;

class apple {
public:
	apple(double p1, double p2) {
		w = p1;
		v = p2;
	}
	double w, v;

};

bool cmp(apple &a1, apple &a2) {//��ƻ�������Լ۱�����
	return a1.v / a1.w > a2.v / a2.w;
}

int main() {
	int t;
	cin >> t;

	while (t--) {
		double n, c;
		cin >> n >> c;
		vector<apple> a;
		for (int i = 0; i < n; i++) {
			double p1, p2;
			cin >> p1 >> p2;
			apple tmp(p1, p2);
			a.push_back(tmp);
		}
		sort(a.begin(), a.end(), cmp);//�����õ���ǰ�涨���cmp����
		double ans = 0;
		for(int i=0;i<n;i++){
			if (c == 0)break;
			double res = min(a[i].w, c);
			ans += res / a[i].w * a[i].v;
			c -= res;
		}
		cout <<fixed<<setprecision(2) << ans << endl;

	}
}