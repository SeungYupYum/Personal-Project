# ==============================CS-199==================================
# FILE:			MyAI.py
#
# AUTHOR: 		Justin Chung
#
# DESCRIPTION:	This file contains the MyAI class. You will implement your
#				agent in this file. You will write the 'getAction' function,
#				the constructor, and any additional helper functions.
#
# NOTES: 		- MyAI inherits from the abstract AI class in AI.py.
#
#				- DO NOT MAKE CHANGES TO THIS FILE.
# ==============================CS-199==================================

from AI import AI
from Action import Action
import math
import random

class MyAI( AI ):

	def __init__(self, rowDimension, colDimension, totalMines, startX, startY):

		########################################################################
		#							YOUR CODE BEGINS						   #
		########################################################################
		self.__rowDimension = rowDimension
		self.__colDimension = colDimension
		self.__totalMines = totalMines
		self.__totalTile = colDimension * rowDimension
		self.__startX = startX
		self.__startY = startY
		self.__found_mine = 0
        # Track visited cells and safe cells to explore
		self.__visited = set()  # Stores visited cells
		self.__complete = set() # Stores cell where there is no uncovered tile
		self.__uncomplete = set()
		self.__safe_cells = []  # Stores safe cells to explore, original(x, y)
		self.__safe_cells.append((self.__startX, self.__startY))

		self.__visited.add((self.__startX, self.__startY)) # Original (x, y)
		self.__complete.add((self.__startX, self.__startY)) # Original (x, y)
		self.__current_cell = (self.__startX, self.__startY)
		self.__cell_hint_map = {}			# tile - hint number
		self.__covered_map = [[0 for _ in range(colDimension)] for _ in range(rowDimension)] # all 0, covoered = 1, flag = -1, other floating number = probability
		
		########################################################################
		#							YOUR CODE ENDS							   #
		########################################################################
	def print_covered_map(self):
		i = 0
		for row in self.__covered_map:
			print(i, row)
			i += 1
	
	def uncover_area_percentage(self):
		cover_tile = 0
		for i in range(0, self.__rowDimension):
			for j in range(0, self.__colDimension):
				if self.__covered_map[i][j] == 1 or self.__covered_map[i][j] == -1:
					cover_tile += 1
		
		return (self.__totalTile - cover_tile) / self.__totalTile
	
	def is_all_corner_opened(self):
		all_corner_open = True

		# Top - Left
		if (
			(self.__covered_map[0][0] == 0) and (self.__covered_map[0][1] == 0) and (self.__covered_map[1][0] == 0) and (self.__covered_map[1][1] == 0) and
		(self.__covered_map[0][self.__colDimension - 1] == 0) and (self.__covered_map[0][self.__colDimension - 2] == 0) and (self.__covered_map[1][self.__colDimension - 1] == 0) and (self.__covered_map[1][self.__colDimension - 2] == 0) and
		(self.__covered_map[self.__rowDimension - 1][0] == 0) and (self.__covered_map[self.__rowDimension - 1][1] == 0) and (self.__covered_map[self.__rowDimension - 2][0] == 0) and (self.__covered_map[self.__rowDimension - 2][1] == 0) and
		(self.__covered_map[self.__rowDimension - 1][self.__colDimension - 1] == 0) and (self.__covered_map[self.__rowDimension - 1][self.__colDimension - 2] == 0 ) and (self.__covered_map[self.__rowDimension - 2][self.__colDimension - 1] == 0) and (self.__covered_map[self.__rowDimension - 2][self.__colDimension - 2] == 0)
			):	
			all_corner_open = False

		return all_corner_open

	def not_opened_corner(self):
		not_opened_corner = []

		# Top - Left
		if (self.__covered_map[0][0] == 0) and (self.__covered_map[0][1] == 0) and (self.__covered_map[1][0] == 0) and (self.__covered_map[1][1] == 0):
			x_coordinate = 0
			y_coordinate = self.__rowDimension - 1 - 0
			not_opened_corner.append((x_coordinate, y_coordinate))
		
		# Top - Right
		if (self.__covered_map[0][self.__colDimension - 1] == 0) and (self.__covered_map[0][self.__colDimension - 2] == 0) and (self.__covered_map[1][self.__colDimension - 1]) and (self.__covered_map[1][self.__colDimension - 2] == 0):
			x_coordinate = self.__colDimension - 1
			y_coordinate = self.__rowDimension - 1 - 0
			not_opened_corner.append((x_coordinate, y_coordinate))
		
		# Bottom - Left
		if (self.__covered_map[self.__rowDimension - 1][0] == 0) and (self.__covered_map[self.__rowDimension - 1][1] == 0) and (self.__covered_map[self.__rowDimension - 2][0] == 0) and (self.__covered_map[self.__rowDimension - 2][1] == 0):
			x_coordinate = 0
			y_coordinate = 0
			not_opened_corner.append((x_coordinate, y_coordinate))

		# Bottom - Right
		if (self.__covered_map[self.__rowDimension - 1][self.__colDimension - 1] == 0) and (self.__covered_map[self.__rowDimension - 1][self.__colDimension - 2] == 0 ) and (self.__covered_map[self.__rowDimension - 2][self.__colDimension - 1] == 0) and (self.__covered_map[self.__rowDimension - 2][self.__colDimension - 2] == 0):
			x_coordinate = self.__colDimension - 1
			y_coordinate = 0
			not_opened_corner.append((x_coordinate, y_coordinate))
		
		return not_opened_corner
	
	def complete_check(self, original_coordinate):
		x, y = original_coordinate
		i_coordinate = self.__rowDimension - 1 - y
		j_coordinate = x

		number_of_uncovered_tile = 0
		for i in range(max(0, i_coordinate - 1), min(self.__rowDimension, i_coordinate + 2)):
			for j in range(max(0, j_coordinate - 1), min(self.__colDimension, j_coordinate + 2)):
				if self.__covered_map[i][j] == 0:
					number_of_uncovered_tile += 1
		
		if number_of_uncovered_tile == 0:
			self.__complete.add(original_coordinate)
		else:
			self.__uncomplete.add(original_coordinate)

	def get_probability(self):
		# Even if we have 2 as hint, and 3 uncovered mine, the probability of each cell can have mine is 2/3
		# Therefore, the probability formula is hint/uncovered tile
		# Since we don't need to compute all the tile, firstly figure out only tiles that need to be compute the probability
		# Since it is what we 'assume' it is safe to delete all assumed mine after we select one and decide to cover.
		# Therefore, this function should return the list of place of assumed mine location wihout any action

		# tile that needs to compute probability, store (i, j)
		uncovered_tile_list = []
		tile_probability_map = {}
		
		for coordinate in self.__visited:
			x, y = coordinate
			i_in_covered_map = self.__rowDimension - 1 - y
			j_in_covered_map = x
			current_uncover_tile_list = []
			number_of_found_mine = 0

			for i in range(i_in_covered_map - 1, i_in_covered_map + 2):
				for j in range(j_in_covered_map - 1, j_in_covered_map + 2):
					# visited node's uncovered tile list
					if (i >= 0 and i < self.__rowDimension) and (j >= 0 and j < self.__colDimension):					
						# If we found uncovered tile, then calculate the probability
						if self.__covered_map[i][j] == 0:
							current_uncover_tile_list.append((i, j))
							if (i,j) not in uncovered_tile_list:
								uncovered_tile_list.append((i,j))
	
						if self.__covered_map[i][j] == -1:
							number_of_found_mine += 1

			if current_uncover_tile_list:
				number_of_mine = self.__cell_hint_map[coordinate] - number_of_found_mine
				probability = number_of_mine / len(current_uncover_tile_list)
				for tile in current_uncover_tile_list:
					if tile in tile_probability_map:
						tile_probability_map[tile] += probability
					else:
						tile_probability_map[tile] = probability

		highest_mine_location = []
		best_probability = 0
		for tile in tile_probability_map:
			if tile_probability_map[tile] > best_probability or math.isclose(tile_probability_map[tile], best_probability):
				best_probability = tile_probability_map[tile]
		
		for tile in tile_probability_map:
			if math.isclose(tile_probability_map[tile], best_probability):
				highest_mine_location.append(tile)

		return highest_mine_location

	def covered_map_update_ver1(self):
		for i in range(0, self.__rowDimension):
			for j in range (0, self.__colDimension):
				if self.__covered_map[i][j] != 0 and self.__covered_map[i][j] != -1:
					# It includes 0 and -1(uncovered cell and mine)
					number_of_uncovered = 0
					# It only counts -1 (mine)
					uncovered_list = []
					# go neighbor of current position in covered map, count 0 and -1
					for x in range (max(0, i - 1), min(i + 2, self.__rowDimension)):
						for y in range(max(0, j - 1), min(j + 2, self.__colDimension)):
							if self.__covered_map[x][y] == 0:
								number_of_uncovered += 1
								uncovered_list.append((x,y))
							if self.__covered_map[x][y] == -1:
								number_of_uncovered += 1

					i_of_current = i
					j_of_current = j
					x_coordinate = j_of_current
					y_coordinate = self.__rowDimension - 1 - i_of_current
					
					# If uncovered tile number is equal to the hint number, then all of them is -1, including already declared mine
					if (x_coordinate, y_coordinate) in self.__cell_hint_map:
						if self.__cell_hint_map[(x_coordinate, y_coordinate)] == number_of_uncovered:
							for coordinate in uncovered_list:
								i_covered_map, j_covered_map = coordinate
								self.__covered_map[i_covered_map][j_covered_map] = -1
				
		# Now 100% mine is updated, looping covered map again, find all the tiles where hint number = near mine count
		for i in range(0, self.__rowDimension):
			for j in range (0, self.__colDimension):
				if self.__covered_map[i][j] != 0 and self.__covered_map[i][j] != -1:

					uncovered_list = []
					number_of_mine = 0

					for x in range (max(0, i - 1), min(i + 2, self.__rowDimension)):
						for y in range(max(0, j - 1), min(j + 2, self.__colDimension)):
							if self.__covered_map[x][y] == 0:
								uncovered_list.append((x, y))
							if self.__covered_map[x][y] == -1:
								number_of_mine += 1

					i_of_current = i
					j_of_current = j
					x_coordinate = j_of_current
					y_coordinate = self.__rowDimension - 1 - i_of_current

					if (x_coordinate, y_coordinate) in self.__cell_hint_map:
						if self.__cell_hint_map[(x_coordinate, y_coordinate)] == number_of_mine:
							for coordinate in uncovered_list:
								i_covered_map, j_covered_map = coordinate
								x_for_cell = j_covered_map
								y_for_cell = self.__rowDimension - 1 - i_covered_map
								
								if (x_for_cell, y_for_cell) not in self.__visited and (x_for_cell, y_for_cell) not in self.__safe_cells:
									self.__safe_cells.append((x_for_cell, y_for_cell))

	def covered_map_update_ver2(self):
		# ver1 is check only case where number of uncover tile = tile's number
		# It does not cover case like:
		#  M  2  M  #
		#  x  4  2  #
		#  x  2  M  #
		#  x  x  x  #
		# Above case, either '2's left top or left has to be mine, which solve 2's bottom row make safe.

		# To solve this problem, go around each tile, mark uncover tile / (hint - found mine), after update, check all near next tile.
		# If sum of near tile's around uncover tile = near tile (hint - found mine) = then near tiles uncover mine that has no number is safe tile
		# Above example:
		#  M    2  M  #
		#  0.5  4  2  #
		#  0.5  2  M  #
		#  x    x  x  #	

		# In here, 0.5 + 0.5 = 1 = 2 - 1
		# This step must be after complete version 1
		# It takes too long time -> Need 1 more data structure called complete set
		# In complete set, it only conatins true (x, y) value, and it only continas tiles where it has no uncover tile.
		# Complete set needs to be update whenever self.__visited is update.
		
		# Update complete set first
		self.__complete = set()
		self.__uncomplete = set()

		for i in range(0, self.__rowDimension):
			for j in range(0, self.__colDimension):
				
				x = j
				y = self.__rowDimension - 1 - i
				if (x,y) in self.__visited and ((x,y) not in self.__complete or (x,y) not in self.__uncomplete):
					self.complete_check((x, y))
		
		for original_coordinate in self.__uncomplete:
			x_coordinate, y_coordinate = original_coordinate
			# Get neightbor uncovered list
			uncovered_neighbor = []
			for x in range(max(0, x_coordinate - 1), min(self.__colDimension, x_coordinate + 2)):
				for y in range(max(0, y_coordinate - 1), min(self.__rowDimension, y_coordinate + 2)):
					if (x, y) in self.__uncomplete and (x, y) != original_coordinate:
						uncovered_neighbor.append((x, y))

			i_coordinate = self.__rowDimension - 1 - y_coordinate
			j_coordinate = x_coordinate

			# From covered map, get 0's position, number of -1 in neighbor
			zero_position = []
			number_of_mine = 0
			for i in range(max(0, i_coordinate - 1), min(self.__rowDimension, i_coordinate + 2)):
				for j in range(max(0, j_coordinate - 1), min(self.__colDimension, j_coordinate + 2)):
					if self.__covered_map[i][j] == 0:
						zero_position.append((i, j))
					if self.__covered_map[i][j] == -1:
						number_of_mine += 1
	
			# Get Prob of each cell
			if zero_position:
				hint = self.__cell_hint_map[(original_coordinate)]
				
				prob = (hint - number_of_mine) / len(zero_position)

				# put prob into all zero position
				for position in zero_position:
					i, j = position
					self.__covered_map[i][j] = prob

				# each uncover neighbor, going thorugh their neightbor, and sum all number that is not 1 and -1 (since 0 has no effect)
				for tile in uncovered_neighbor:
					# print("Current tile: ", tile)
					x, y = tile
					i_coordinate = self.__rowDimension - 1 - y
					j_coordinate = x

					zero_position_neighbor = []
					sum_of_prob = 0
					num_mine = 0

					for i in range(max(0, i_coordinate - 1), min(self.__rowDimension, i_coordinate + 2)):
						for j in range(max(0, j_coordinate - 1), min(self.__colDimension, j_coordinate + 2)):
							if self.__covered_map[i][j] == 0:
								zero_position_neighbor.append((i, j))
							if self.__covered_map[i][j] == -1:
								num_mine += 1
							if self.__covered_map[i][j] != 1 and self.__covered_map[i][j] != -1:
								# print("added: ", i, j)
								sum_of_prob += self.__covered_map[i][j]

					# If sum of prob = its hint - num mine, all zero is safe
					hint = self.__cell_hint_map[tile]
					if math.isclose(sum_of_prob, hint - num_mine):
						for position in zero_position_neighbor:
							i, j = position
							x = j
							y = self.__rowDimension - 1 - i
							if (x,y) not in self.__safe_cells:
								self.__safe_cells.append((x, y))

				# After check neighbor, delete prob
				for position in zero_position:
					i, j = position
					self.__covered_map[i][j] = 0

	def logical_safe_cell(self):
		# Cover all logical safe cell.
		# For basic level, it must invole 1.
		# For example,
		# x  x  x  x
		# x  1  2  c
		# x  x  c  c
		# In this case, top - right corner must mine, and either (1,2) or (1,3) must be mine
		# Therefore, all tiles other than (1,2), (1,3) guranteed safe cell.

		# Solution:
		# From uncomplete cell, find all location of 1.
		# For each location of 1, find left / right / up / down cell
		# if one of them hint number is greater than 1, and its uncover cell that is not part of 1's uncover cell is less than or equal to (hint - 1)
		# Then it is guranteed at least one mine must be in the 1's area.

		# Complete and Uncomplete set update first
		self.__complete = set()
		self.__uncomplete = set()
		for i in range(0, self.__rowDimension):
			for j in range(0, self.__colDimension):
				
				x = j
				y = self.__rowDimension - 1 - i
				if (x,y) in self.__visited and ((x,y) not in self.__complete or (x,y) not in self.__uncomplete):
					self.complete_check((x, y))
		
		# Get all 1 list, it should include current hint number is 1.
		# Including (i, j) format.
		uncomplete_one_list = []

		for tile in self.__uncomplete:
			x, y = tile
			i_coordinate = self.__rowDimension - 1 - y
			j_coordinate = x

			num_mine = 0
			for i in range(max(0, i_coordinate - 1), min(self.__rowDimension, i_coordinate + 2)):
				for j in range(max(0, j_coordinate - 1), min(self.__colDimension, j_coordinate + 2)):
					if self.__covered_map[i][j] == -1:
						num_mine += 1

			hint = self.__cell_hint_map[(tile)]

			if hint - num_mine == 1:
				uncomplete_one_list.append((i_coordinate, j_coordinate))
		# From 1 list, check left, right, up, down
		# All of them must be in the uncomplete set, Otherwise, useless to check logical safe tile
		# Before check, store uncover tile location first
		# To achieve efficiency, use set() to store uncover position, in the future, use intersection.
		for coordinate in uncomplete_one_list:
			i_coordinate, j_coordinate = coordinate
			uncover_position = set()

			for i in range(max(0, i_coordinate - 1), min(self.__rowDimension, i_coordinate + 2)):
				for j in range(max(0, j_coordinate - 1), min(self.__colDimension, j_coordinate + 2)):
					if self.__covered_map[i][j] == 0:
						uncover_position.add((i, j))
			# Find Up, Down, Left, Right.
			# Whenever it finds, go its neighbor, 
			# 1) count mine and uncover tile (uncover tile not include mine)
			# 2) length of uncover tile that is not intersect with 1's uncover tile
			# 3) get (hint - covered mine so far)
			# 4) if length of uncover tile that is not intersect with is smaller than 3 result, all 1's neighbor that is not intersect is safe tile.
			for i in range(max(0, i_coordinate - 1), min(self.__rowDimension, i_coordinate + 2)):
				for j in range(max(0, j_coordinate - 1), min(self.__colDimension, j_coordinate + 2)):
					# UP
					if i == i_coordinate + 1 and j == j_coordinate:
						up_i_coordinate = i
						up_j_coordinate = j
						up_x_coordinate = up_j_coordinate
						up_y_coordinate = self.__rowDimension - 1 - up_i_coordinate
						if (up_x_coordinate, up_y_coordinate) in self.__uncomplete:
							num_mine = 0
							uncover_position2 = set()

							for i2 in range(max(0, up_i_coordinate - 1), min(self.__rowDimension, up_i_coordinate + 2)):
								for j2 in range(max(0, up_j_coordinate - 1), min(self.__colDimension, up_j_coordinate + 2)):
									if self.__covered_map[i2][j2] == -1:
										num_mine += 1
									if self.__covered_map[i2][j2] == 0:
										uncover_position2.add((i2,j2))
							intersection = uncover_position.intersection(uncover_position2)
							intersection_length = len(intersection)

							if intersection_length != 0:
								hint = self.__cell_hint_map[(up_x_coordinate, up_y_coordinate)]
								current_mine = hint - num_mine
								not_intersect = len(uncover_position2.difference(uncover_position))
								# If the number of left over mine is greater than not insertect tile, then must one go to the intersect
								# Therefore, 1's all uncover tile that is not in the interesct is safe tile
								if current_mine > not_intersect:
									one_not_intersect = uncover_position.difference(uncover_position2)
									
									for coordinate in one_not_intersect:
										i, j = coordinate
										x = j
										y = self.__rowDimension - 1 - i
										if (x, y) not in self.__safe_cells:
											self.__safe_cells.append((x, y))
					# DOWN
					if i == i_coordinate - 1 and j == j_coordinate:
						down_i_coordinate = i
						down_j_coordinate = j
						down_x_coordinate = down_j_coordinate
						down_y_coordinate = self.__rowDimension - 1 - down_i_coordinate
						if (down_x_coordinate, down_y_coordinate) in self.__uncomplete:
							num_mine = 0
							uncover_position2 = set()

							for i2 in range(max(0, down_i_coordinate - 1), min(self.__rowDimension, down_i_coordinate + 2)):
								for j2 in range(max(0, down_j_coordinate - 1), min(self.__colDimension, down_j_coordinate + 2)):
									if self.__covered_map[i2][j2] == -1:
										num_mine += 1
									if self.__covered_map[i2][j2] == 0:
										uncover_position2.add((i2,j2))
							intersection = uncover_position.intersection(uncover_position2)
							intersection_length = len(intersection)

							if intersection_length != 0:
								hint = self.__cell_hint_map[(down_x_coordinate, down_y_coordinate)]
								current_mine = hint - num_mine
								not_intersect = len(uncover_position2.difference(uncover_position))
								# If the number of left over mine is greater than not insertect tile, then must one go to the intersect
								# Therefore, 1's all uncover tile that is not in the interesct is safe tile
								if current_mine > not_intersect:
									one_not_intersect = uncover_position.difference(uncover_position2)
									
									for coordinate in one_not_intersect:
										i, j = coordinate
										x = j
										y = self.__rowDimension - 1 - i
										if (x, y) not in self.__safe_cells:
											self.__safe_cells.append((x, y))						
					# LEFT
					if i == i_coordinate and j == j_coordinate - 1:
						left_i_coordinate = i
						left_j_coordinate = j
						left_x_coordinate = left_j_coordinate
						left_y_coordinate = self.__rowDimension - 1 - left_i_coordinate
						if (left_x_coordinate, left_y_coordinate) in self.__uncomplete:
							num_mine = 0
							uncover_position2 = set()

							for i2 in range(max(0, left_i_coordinate - 1), min(self.__rowDimension, left_i_coordinate + 2)):
								for j2 in range(max(0, left_j_coordinate - 1), min(self.__colDimension, left_j_coordinate + 2)):
									if self.__covered_map[i2][j2] == -1:
										num_mine += 1
									if self.__covered_map[i2][j2] == 0:
										uncover_position2.add((i2,j2))
							intersection = uncover_position.intersection(uncover_position2)
							intersection_length = len(intersection)

							if intersection_length != 0:
								hint = self.__cell_hint_map[(left_x_coordinate, left_y_coordinate)]
								current_mine = hint - num_mine
								not_intersect = len(uncover_position2.difference(uncover_position))
								# If the number of left over mine is greater than not insertect tile, then must one go to the intersect
								# Therefore, 1's all uncover tile that is not in the interesct is safe tile
								if current_mine > not_intersect:
									one_not_intersect = uncover_position.difference(uncover_position2)
									
									for coordinate in one_not_intersect:
										i, j = coordinate
										x = j
										y = self.__rowDimension - 1 - i
										if (x, y) not in self.__safe_cells:
											self.__safe_cells.append((x, y))	
					# RRIGHT
					if i == i_coordinate and j == j_coordinate + 1:
						right_i_coordinate = i
						right_j_coordinate = j
						right_x_coordinate = right_j_coordinate
						right_y_coordinate = self.__rowDimension - 1 - right_i_coordinate
						if (right_x_coordinate, right_y_coordinate) in self.__uncomplete:
							num_mine = 0
							uncover_position2 = set()

							for i2 in range(max(0, right_i_coordinate - 1), min(self.__rowDimension, right_i_coordinate + 2)):
								for j2 in range(max(0, right_j_coordinate - 1), min(self.__colDimension, right_j_coordinate + 2)):
									if self.__covered_map[i2][j2] == -1:
										num_mine += 1
									if self.__covered_map[i2][j2] == 0:
										uncover_position2.add((i2,j2))
							intersection = uncover_position.intersection(uncover_position2)
							intersection_length = len(intersection)

							if intersection_length != 0:
								hint = self.__cell_hint_map[(right_x_coordinate, right_y_coordinate)]
								current_mine = hint - num_mine
								not_intersect = len(uncover_position2.difference(uncover_position))
								# If the number of left over mine is greater than not insertect tile, then must one go to the intersect
								# Therefore, 1's all uncover tile that is not in the interesct is safe tile
								if current_mine > not_intersect:
									one_not_intersect = uncover_position.difference(uncover_position2)
									
									for coordinate in one_not_intersect:
										i, j = coordinate
										x = j
										y = self.__rowDimension - 1 - i
										if (x, y) not in self.__safe_cells:
											self.__safe_cells.append((x, y))

	def number_of_find_mine(self):
		number_of_mine = 0
		for i in range(0, self.__rowDimension):
			for j in range(0, self.__colDimension):
				if self.__covered_map[i][j] == -1:
					number_of_mine += 1
		
		return number_of_mine

	def covered_percentage(self):
		zero_tile = 0
		for i in range(0, self.__rowDimension):
			for j in range(0, self.__colDimension):
				if self.__covered_map[i][j] == 0:
					zero_tile += 1
		
		covered_tile = self.__totalTile - zero_tile
		return (covered_tile / self.__totalTile) * 100
	
	def complete_zero_list(self):
		complete_zero_list = []
		for i in range(0, self.__rowDimension):
			for j in range(0, self.__colDimension):
				x_coordinate = j
				y_coordinate = self.__rowDimension - 1 - i

				if (x_coordinate, y_coordinate) not in self.__visited and self.__covered_map[i][j] == 0:
					zero_count = 0
					num_tile = 0
					for i2 in range(max(0, i - 1), min(self.__rowDimension, i + 2)):
						for j2 in range(max(0, j - 1), min(self.__rowDimension, j + 2)):
							num_tile += 1

							if self.__covered_map[i2][j2] == 0:
								zero_count += 1
					if zero_count == num_tile:
						if (x_coordinate, y_coordinate) not in complete_zero_list:
							complete_zero_list.append((x_coordinate, y_coordinate))
		return complete_zero_list

	def remove_mine(self):
		for x_y in self.__visited:
			x, y = x_y
			hint = self.__cell_hint_map[x_y]
			i_coordinate = self.__rowDimension - 1 - y
			j_coordinate = x

			num_mine = 0
			for i in range(max(0, i_coordinate - 1), min(self.__rowDimension, i_coordinate + 2)):
				for j in range(max(0, j_coordinate - 1), min(self.__rowDimension, j_coordinate + 2)):
					if self.__covered_map[i][j] == -1:
						num_mine += 1

			if num_mine > hint:
				for i in range(max(0, i_coordinate - 1), min(self.__rowDimension, i_coordinate + 2)):
					for j in range(max(0, j_coordinate - 1), min(self.__rowDimension, j_coordinate + 2)):
						if self.__covered_map[i][j] == -1:
							self.__covered_map[i][j] = 0

	def getAction(self, number: int) -> "Action Object":
			
		########################################################################
		#							YOUR CODE BEGINS						   #
		########################################################################
		# x = j <-> j = x
		# y = row dimension - 1 - i, i = row dimension - 1 - y
		########################################################################		
		
		# current cell is just opended cell
		x, y = self.__current_cell
		self.__covered_map[self.__rowDimension - 1 - y][x] = 1
		self.__cell_hint_map[self.__current_cell] = number
		#If we have safe cell
		if self.__safe_cells:
			# If there is safe cell, and the number is 0, then add all neghbor to the safe cell
			if number == 0:

				for i in range((x - 1), (x + 2)):
					for j in range((y - 1), (y + 2)):
						if (i >= 0 and i < self.__colDimension) and (j >= 0 and j < self.__rowDimension):
							if (i, j) not in self.__visited and (i, j) not in self.__safe_cells:
								self.__safe_cells.append((i, j))

				self.__current_cell = self.__safe_cells.pop(0)
				self.__visited.add(self.__current_cell)
				x, y = self.__current_cell
				return Action(AI.Action.UNCOVER, x, y)
			# If there is safe cell, and the number is not 0, then just open safe cell without adding neighbor, since we don't know
			else:
				self.__current_cell = self.__safe_cells.pop(0)
				self.__visited.add(self.__current_cell)
				x, y = self.__current_cell
				return Action(AI.Action.UNCOVER, x, y)
		# If we don't have safe cell, update it from covered_map
		else:
			if number == 0:
				for i in range((x - 1), (x + 2)):
					for j in range((y - 1), (y + 2)):
						if (i >= 0 and i < self.__colDimension) and (j >= 0 and j < self.__rowDimension):
							if (i, j) not in self.__visited and (i, j) not in self.__safe_cells:
								self.__safe_cells.append((i, j))
				if self.__safe_cells:
					self.__current_cell = self.__safe_cells.pop(0)
					self.__visited.add(self.__current_cell)
					x, y = self.__current_cell
					return Action(AI.Action.UNCOVER, x, y)
			self.covered_map_update_ver1()
			self.covered_map_update_ver2()
			self.logical_safe_cell()

			# safe cell is updated, now pop and action
			if self.__safe_cells:
				self.__current_cell = self.__safe_cells.pop(0)
				self.__visited.add(self.__current_cell)
				x, y = self.__current_cell
				return Action(AI.Action.UNCOVER, x, y)
			else:
				# Now involves probability				
				if len(self.__visited) + self.__totalMines == self.__totalTile:
					return Action(AI.Action.LEAVE)
				
				if self.number_of_find_mine() == self.__totalMines:
					for i in range(0, self.__rowDimension):
						for j in range(0, self.__colDimension):
							if self.__covered_map[i][j] == 0:
								x = j
								y = self.__rowDimension - 1 - i
								self.__safe_cells.append((x, y))
					self.__current_cell = self.__safe_cells.pop(0)
					self.__visited.add(self.__current_cell)
					x, y = self.__current_cell
					return Action(AI.Action.UNCOVER, x, y)
				if self.number_of_find_mine() > self.__totalMines:
					self.remove_mine()
					self.covered_map_update_ver1()
					self.covered_map_update_ver2()
					self.logical_safe_cell()
				else:
					# Check the portion of uncover area. If it is less than 1/4 of whole tile, to probability,
					# Otherwise, click corner (it's natural human approach)
					assumed_mine = None
					if self.is_all_corner_opened():
						highest_mine_location_list = self.get_probability()
						if highest_mine_location_list:
							i, j = highest_mine_location_list.pop(0)
							assumed_mine = (i,j)
							self.__covered_map[i][j] = -1
							self.__found_mine += 1
							self.covered_map_update_ver1()
							self.covered_map_update_ver2()
							self.logical_safe_cell()
					else:
						not_opened_corner = self.not_opened_corner()
						random_corner = random.choice(not_opened_corner)
						self.__safe_cells.append(random_corner)

					if self.__safe_cells:
						if assumed_mine is not None:
							i, j = assumed_mine
							self.__covered_map[i][j] = 0
						self.__current_cell = self.__safe_cells.pop(0)
						self.__visited.add(self.__current_cell)
						x, y = self.__current_cell
						return Action(AI.Action.UNCOVER, x, y)
					else:
						# Pick random place where all neighbor is 0
						if assumed_mine is not None:
							i, j = assumed_mine
							self.__covered_map[i][j] = 0
						if self.covered_percentage() < 80:
							complete_zero_list = self.complete_zero_list()
							if complete_zero_list:
								self.__current_cell = random.choice(complete_zero_list)
								self.__visited.add(self.__current_cell)
								x, y = self.__current_cell
								return Action(AI.Action.UNCOVER, x, y)
							else:
								zero_list = []
								for i in range(0, self.__rowDimension):
									for j in range(0, self.__colDimension):
										if self.__covered_map[i][j] == 0:
											zero_list.append((i,j))
								
								zero_mine_map = {}

								for i_j in zero_list:
									i_coordinate, j_coordinate = i_j
									num_mine = 0
									for i in range(max(0, i_coordinate - 1), min(self.__rowDimension, i_coordinate + 2)):
										for j in range(max(0, j_coordinate - 1), min(self.__rowDimension, j_coordinate + 2)):
											if self.__covered_map[i][j] == -1:
												num_mine += 1
									zero_mine_map[i_j] = num_mine

								max_mine_tile = max(zero_mine_map, key=lambda k: zero_mine_map[k])
								i, j = max_mine_tile
								x = j
								y = self.__rowDimension - 1 - i
								self.__current_cell = (x, y)
								self.__visited.add(self.__current_cell)
								x, y = self.__current_cell
								return Action(AI.Action.UNCOVER, x, y)
						else:
							zero_list = []
							for i in range(0, self.__rowDimension):
								for j in range(0, self.__colDimension):
									if self.__covered_map[i][j] == 0:
										zero_list.append((i,j))
							
							zero_mine_map = {}

							for i_j in zero_list:
								i_coordinate, j_coordinate = i_j
								num_mine = 0
								for i in range(max(0, i_coordinate - 1), min(self.__rowDimension, i_coordinate + 2)):
									for j in range(max(0, j_coordinate - 1), min(self.__rowDimension, j_coordinate + 2)):
										if self.__covered_map[i][j] == -1:
											num_mine += 1
								zero_mine_map[i_j] = num_mine

							max_mine_tile = max(zero_mine_map, key=lambda k: zero_mine_map[k])
							i, j = max_mine_tile
							x = j
							y = self.__rowDimension - 1 - i
							self.__current_cell = (x, y)
							self.__visited.add(self.__current_cell)
							x, y = self.__current_cell
							return Action(AI.Action.UNCOVER, x, y)
		########################################################################
		#							YOUR CODE ENDS							   #
		########################################################################
