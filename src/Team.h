#pragma once

enum TEAM {
	TEAM_RED,
	TEAM_BLUE
};


class Team {
protected:
	TEAM m_team;
public:
	TEAM getTeam() {
		return m_team;
	}
};