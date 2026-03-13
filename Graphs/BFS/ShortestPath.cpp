#include <iostream>
#include <vector>
#include <queue>
#include <utility>

void shortestPath(std::pair<int,int> start, std::pair<int, int> end, const std::vector<std::vector<int>>& grid) {
	int m = grid.size();
	int n = grid[0].size();
	std::queue<std::pair<int,int>> q;
	std::vector<std::vector<bool>> visited(m, std::vector<bool>(n,false));

	int dx[4] = {1,-1,0,0};
	int dy[4] = {0,0,1,-1};
	q.push(start);
	visited[start.first][start.second] = true;
	int level = 0;
	while(!q.empty()) {
		int sz = q.size();
		std::cout << "Level " << level << ": ";
		for(int i=0;i<sz;i++) {
			auto [x,y] = q.front();
			q.pop();
			std::cout << "(" << x << "," << y << ") ";
			if (x == end.first && y == end.second)
				return ;
			for(int j=0; j<4; j++) {
				int nx = x + dx[j];
				int ny = y + dy[j];
				if(nx < 0 || ny < 0 || nx >= m || ny >= n)
					continue;
				if(visited[nx][ny] || grid[nx][ny] == 1)
					continue;
				visited[nx][ny] = true;
				q.push({nx,ny});
			}
		}
		std::cout << "\n";
		level++;
	}
}

int main() {
	std::vector<std::vector<int>> grid = {
		{0,0,0,0},
		{1,1,0,1},
		{0,0,0,0},
		{0,1,1,0}
	};
	std::pair<int,int> start = {0,0};
	std::pair<int,int> end = {3,3};
	shortestPath(start, end, grid);

	return 0;
}
