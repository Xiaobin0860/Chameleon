/*
  Chameleon, a UCI Chinese Chess playing engine derived from Stockfish 7
  Copyright (C) 2004-2008 Tord Romstad (Glaurung author)
  Copyright (C) 2008-2015 Marco Costalba, Joona Kiiski, Tord Romstad
  Copyright (C) 2015-2017 Marco Costalba, Joona Kiiski, Gary Linscott, Tord Romstad
  Copyright (C) 2017 Wilbert Lee

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef TIMEMAN_H_INCLUDED
#define TIMEMAN_H_INCLUDED

#include "misc.h"
#include "search.h"
#include "thread.h"

// The TimeManagement class computes the optimal time to think depending on
// the maximum available time, the game move number and other parameters.
class TimeManagement
{
public:
  void init(Search::LimitsType& limits, Color us, int ply);
  void pv_instability(double bestMoveChanges) { unstablePvFactor = 1 + bestMoveChanges; }
  int available() const { return int(optimumTime * unstablePvFactor * 1.016); }
  int maximum() const { return maximumTime; }
  int elapsed() const { return int(Search::Limits.npmsec ? Threads.nodes_searched() : now() - startTime); }

  int64_t availableNodes; // When in 'nodes as time' mode

private:
  TimePoint startTime;
  int optimumTime;
  int maximumTime;
  double unstablePvFactor;
};

extern TimeManagement Time;

#endif // #ifndef TIMEMAN_H_INCLUDED
