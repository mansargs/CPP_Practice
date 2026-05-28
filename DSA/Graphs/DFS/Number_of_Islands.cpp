#include <iostream>
#include <vector>

void dfs(int i, int j, std::vector<std::vector<char>>& grid) {
	int rows = grid.size();
	int cols = grid[0].size();
	if (i < 0 || i >= rows || j < 0 || j >= cols || grid[i][j] == '0')
		return;
	grid[i][j] = '0';
	dfs(i+1, j, grid);
	dfs(i-1, j, grid);
	dfs(i, j+1, grid);
	dfs(i, j-1, grid);
}

int number_of_islands(std::vector<std::vector<char>>& grid) {
	if (grid.empty())
		return 0;
	int count = 0;
	int rows = grid.size(), cols = grid[0].size();
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (grid[i][j] == '1') {
				++count;
				dfs(i, j, grid);
			}
		}
	}
	return count;
}

int main() {
	std::vector<std::vector<char>> grid1 = {
		{'1','1','0'},
		{'0','1','0'},
		{'1','0','1'},
		{'0', '1', '0'}
	};
	std::cout << "Number of islands (Test 1): " << number_of_islands(grid1)
				<< "  // Expected: 4" << std::endl;
}



