#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int total = 1e4;
int t, n, allowed, ans;
pair<int, pair<int, int> > A[5005];

int main() {

	cin >> t;

	for (int q = 1; q <= t; q++) {
		ans = 0;
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> A[i].first >> A[i].second.first >> A[i].second.second;

		for (int i = 0; i < n; i++) {
			// let A[i].st be the amount of juice A
			// the allowed amount for B is 10000-A[i].st
			allowed = total - A[i].first;

			vector<pair<int, int> > v;
			// put all the people that we can potentially satisfy in a vector
			// people that want juice A less or equal to the amount we chose and
			// if their desire of juice B allows it
			for (int j = 0; j < n; j++)
				if (A[j].first <= A[i].first and A[j].second.first <= allowed)
					v.push_back(A[j].second);
			// sort these based on their desire of juice B
			sort(v.begin(), v.end());

			priority_queue<int> PQ;
			for (int j = 0; j < v.size(); j++) {
				// let v[j].st be the amount of juice B
				// push it's desired juice C into the priority queue
				PQ.push(v[j].second);
				// now everything in the priority queue is satisfied with juice A and juice B
				// but if a person's desire of juice C + our chosen juice A + our chosen juice B exceeds 10000
				// we can not satisfy that person, since here juice A and juice B is chosen already
				// we use a priority queue that will sort the current people by their desire of juice C
				// while the biggest juice C desire plus the chosen values exceed 10000, we pop from the priority queue
				while (PQ.size() and PQ.top() + v[j].first + A[i].first > total)
					PQ.pop();
				// we know that the remaining people in the priority queue satisfy our chosen values
				// and no more people can be added
				// thus with this chosen juice A and juice B amount, we can at most satisfy the number
				// of people in the priority queue, so we update the answer if it's more than the current answer
				ans = max(ans, (int)PQ.size());
			}
		}
		printf("Case #%d: %d\n", q, ans);
	}

	return 0;
}
