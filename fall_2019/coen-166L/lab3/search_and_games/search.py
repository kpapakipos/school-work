# search.py
# ---------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

import util
import sys
import copy

class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def goalTest(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getActions(self, state):
        """
        Given a state, returns available actions.
        Returns a list of actions
        """        
        util.raiseNotDefined()

    def getResult(self, state, action):
        """
        Given a state and an action, returns resulting state.
        """
        util.raiseNotDefined()

    def getCost(self, state, action):
        """
        Given a state and an action, returns step cost, which is the incremental cost 
        of moving to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()

class Node:
    """
    Search node object for your convenience.

    This object uses the state of the node to compare equality and for its hash function,
    so you can use it in things like sets and priority queues if you want those structures
    to use the state for comparison.

    Example usage:
    >>> S = Node("Start", None, None, 0)
    >>> A1 = Node("A", S, "Up", 4)
    >>> B1 = Node("B", S, "Down", 3)
    >>> B2 = Node("B", A1, "Left", 6)
    >>> B1 == B2
    True
    >>> A1 == B2
    False
    >>> node_list1 = [B1, B2]
    >>> B1 in node_list1
    True
    >>> A1 in node_list1
    False
    """
    def __init__(self, state, parent, action, path_cost):
        self.state = state
        self.parent = parent
        self.action = action
        self.path_cost = path_cost

    def __hash__(self):
        return hash(self.state)

    def __eq__(self, other):
        return self.state == other.state

    def __ne__(self, other):
        return self.state != other.state


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return  [s, s, w, s, w, w, s, w]

def breadthFirstSearch(problem):
    """
    Search the shallowest nodes in the search tree first.

    You are not required to implement this, but you may find it useful for Q5.
    """
    "*** YOUR CODE HERE ***"
    util.raiseNotDefined()

def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

def iterativeDeepeningSearch(problem):
    def recursiveDLS(node, problem, limit, visited):
        if problem.goalTest(node.state):
            return [node.action]
        elif limit == 0:
            return 'cutoff'
        else:
            visited.append(node)
            cutoffOccurred = False
            for action in problem.getActions(node.state):
                child = Node(problem.getResult(node.state, action), node, action, problem.getCost(node.state, action) + node.path_cost)
                if child in visited:
                    continue
                result = recursiveDLS(child, problem, limit - 1, visited)
                if result == 'cutoff':
                    cutoffOccurred = True
                elif result != 'failure':
                    if node.action != None:
                        result.insert(0, node.action)
                    return result
            if cutoffOccurred:
                return 'cutoff'
            else:
                return 'failure'

    depth = 0
    while True:
        visited = []
        result = recursiveDLS(Node(problem.getStartState(), None, None, 0), problem, depth, visited)
        if result != 'cutoff' and result != 'failure':
            return result
        depth += 1


def aStarSearch(problem, heuristic=nullHeuristic):
    def recursiveAStar(node, problem, visited):
        if problem.goalTest(node.state):
            return [node.action]
        else:
            visited.append(node)
            pQueue = util.PriorityQueue()
            for action in problem.getActions(node.state):
                child = Node(problem.getResult(node.state, action), node, action, problem.getCost(node.state, action) + node.path_cost)
                if child in visited:
                    continue
                fOfChild = child.path_cost + heuristic(child.state, problem)
                pQueue.push(child, fOfChild)
            while not pQueue.isEmpty():
                topChildFromQueue = pQueue.pop()
                result = recursiveAStar(topChildFromQueue, problem, visited)
                if result != 'failure':
                    if node.action != None:
                        result.insert(0, node.action)
                    return result
            return 'failure'

    visited = []
    result = recursiveAStar(Node(problem.getStartState(), None, None, 0), problem, visited)
    if result != 'failure':
        return result
    

# Abbreviations
bfs = breadthFirstSearch
astar = aStarSearch
ids = iterativeDeepeningSearch
