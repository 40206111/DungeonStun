#include "LevelSystem.h"
#include <fstream>
#include "system_renderer.h"
#include "../Code/AssetLoader.h"

using namespace std;
using namespace sf;

std::map<LevelSystem::Tile, sf::Color> LevelSystem::_colours{
	{WALL, Color::White}, {END, Color::Red} };

sf::Color LevelSystem::getColor(LevelSystem::Tile t) {
	auto it = _colours.find(t);
	if (it == _colours.end()) {
		_colours[t] = Color::Transparent;
	}
	return _colours[t];
}

void LevelSystem::setColor(LevelSystem::Tile t, sf::Color c) {
	_colours[t] = c;
}

std::unique_ptr<LevelSystem::Tile[]> LevelSystem::_tiles;
size_t LevelSystem::_width;
size_t LevelSystem::_height;

float LevelSystem::_tileSize(100.f);
Vector2f LevelSystem::_offset(0.0f, 30.0f);
// Vector2f LevelSystem::_offset(0,0);
vector<std::shared_ptr<sf::Sprite>> LevelSystem::_sprites;

void LevelSystem::loadLevelFile(const std::string& path, float tileSize) {
	_tileSize = tileSize;
	size_t w = 0, h = 0;
	string buffer;

	// Load in file to buffer
	ifstream f(path);
	if (f.good()) {
		f.seekg(0, std::ios::end);
		buffer.resize(f.tellg());
		f.seekg(0);
		f.read(&buffer[0], buffer.size());
		f.close();
		while (buffer[buffer.size() - 1] == '\0') {
			buffer.pop_back();
		}
	}
	else {
		throw string("Couldn't open level file: ") + path;
	}

	std::vector<Tile> temp_tiles;
	int widthCheck = 0;
	for (int i = 0; i < buffer.size(); ++i) {
		const char c = buffer[i];
		if (c == '\n') { // newline
			if (w == 0) {  // if we haven't written width yet
				w = i;       // set width
			}
			else if (w != (widthCheck - 1)) {
				throw string("non uniform width:" + to_string(h) + " ") + path;
			}
			widthCheck = 0;
			h++; // increment height
		}
		else {
			temp_tiles.push_back((Tile)c);
		}
		++widthCheck;
	}

	if (temp_tiles.size() != (w * h)) {
		throw string("Can't parse level file") + path;
	}
	_tiles = std::make_unique<Tile[]>(w * h);
	_width = w; // set static class vars
	_height = h;
	_tileSize = Renderer::GetWindow().getSize().x / _width;
	std::copy(temp_tiles.begin(), temp_tiles.end(), &_tiles[0]);
	cout << "Level " << path << " Loaded. " << w << "x" << h << std::endl;
	buildTextureSprites();
}

//void LevelSystem::buildSprites(bool optimise) {
//	_sprites.clear();
//
//	struct tp {
//		sf::Vector2f p;
//		sf::Vector2f s;
//		sf::Color c;
//	};
//	vector<tp> tps;
//	const auto tls = Vector2f(_tileSize, _tileSize);
//	for (size_t y = 0; y < _height; ++y) {
//		for (size_t x = 0; x < _width; ++x) {
//			Tile t = getTile({ x, y });
//			if (t == EMPTY) {
//				continue;
//			}
//			tps.push_back({ getTilePosition({x, y}), tls, getColor(t) });
//		}
//	}
//
//	const auto nonempty = tps.size();
//
//	// If tile of the same type are next to each other,
//	// We can use one large sprite instead of two.
//	if (optimise && nonempty) {
//
//		vector<tp> tpo;
//		tp last = tps[0];
//		size_t samecount = 0;
//
//		for (size_t i = 1; i < nonempty; ++i) {
//			// Is this tile compressible with the last?
//			bool same = ((tps[i].p.y == last.p.y) &&
//				(tps[i].p.x == last.p.x + (tls.x * (1 + samecount))) &&
//				(tps[i].c == last.c));
//			if (same) {
//				++samecount; // Yes, keep going
//				// tps[i].c = Color::Green;
//			}
//			else {
//				if (samecount) {
//					last.s.x = (1 + samecount) * tls.x; // Expand tile
//				}
//				// write tile to list
//				tpo.push_back(last);
//				samecount = 0;
//				last = tps[i];
//			}
//		}
//		// catch the last tile
//		if (samecount) {
//			last.s.x = (1 + samecount) * tls.x;
//			tpo.push_back(last);
//		}
//
//		// No scan down Y, using different algo now that compressible blocks may
//		// not be contiguous
//		const auto xsave = tpo.size();
//		samecount = 0;
//		vector<tp> tpox;
//		for (size_t i = 0; i < tpo.size(); ++i) {
//			last = tpo[i];
//			for (size_t j = i + 1; j < tpo.size(); ++j) {
//				bool same = ((tpo[j].p.x == last.p.x) && (tpo[j].s == last.s) &&
//					(tpo[j].p.y == last.p.y + (tls.y * (1 + samecount))) &&
//					(tpo[j].c == last.c));
//				if (same) {
//					++samecount;
//					tpo.erase(tpo.begin() + j);
//					--j;
//				}
//			}
//			if (samecount) {
//				last.s.y = (1 + samecount) * tls.y; // Expand tile
//			}
//			// write tile to list
//			tpox.push_back(last);
//			samecount = 0;
//		}
//
//		tps.swap(tpox);
//	}
//
//	for (auto& t : tps) {
//		auto s = make_unique<sf::RectangleShape>();
//		s->setPosition(t.p);
//		s->setSize(t.s);
//		s->setFillColor(Color::Red);
//		s->setFillColor(t.c);
//		// s->setFillColor(Color(rand()%255,rand()%255,rand()%255));
//		_sprites.push_back(move(s));
//	}
//
//	cout << "Level with " << (_width * _height) << " Tiles, With " << nonempty
//		<< " Not Empty, using: " << _sprites.size() << " Sprites\n";
//}

void LevelSystem::buildTextureSprites() {
	_sprites.clear();

	struct texS {
		sf::Vector2f pos;
		sf::Vector2f size;
		sf::Sprite* tex;
	};
	vector<texS> tiles;
	const auto tSize = Vector2f(_tileSize, _tileSize);
	for (size_t y = 0; y < _height; ++y) {
		for (size_t x = 0; x < _width; ++x) {
			Tile t = getTile({ x, y });
			if (t == EMPTY) {
				continue;
			}
			tiles.push_back({ getTilePosition({ x, y }), tSize, new Sprite() });
		}
	}

	const auto nonempty = tiles.size();

	for (auto& t : tiles) {
		//If tile is a wall
		if (getTileAt({ t.pos.x, t.pos.y }) == WALL)
		{
			Vector2ul current(Vector2ul((t.pos - _offset) / (_tileSize)));
			int yVoid = 0;
			int xVoid = 0;
			int wall1 = 0;
			int wall2 = 0;

			//check what side(s) the edge of the world is on
			if (current.x == 0)
			{
				xVoid = -1;
			}
			else if (current.x == (_width - 1))
			{
				xVoid = 1;
			}
			if (current.y == 0)
			{
				yVoid = -1;
			}
			else if (current.y == (_height - 1))
			{
				yVoid = 1;
			}

			//Find what walls are connected to it
			if (xVoid != -1 && getTile({ current.x - 1, current.y }) == WALL)
			{
				// 4 = left
				if (wall1 == 0)
					wall1 = 4;
				else
					wall2 = 4;
			}
			if (xVoid != 1 && getTile({ current.x + 1, current.y }) == WALL)
			{
				//2 = right
				if (wall1 == 0)
					wall1 = 2;
				else
					wall2 = 2;
			}
			if (yVoid != -1 && getTile({ current.x, current.y - 1 }) == WALL)
			{
				//1 = up
				if (wall1 == 0)
					wall1 = 1;
				else
					wall2 = 1;
			}
			if (yVoid != 1 && getTile({ current.x, current.y + 1 }) == WALL)
			{
				//3 = down
				if (wall1 == 0)
					wall1 = 3;
				else
					wall2 = 3;
			}

			//use correct sprite
			if (wall1 == 1 && wall2 == 2 || wall1 == 2 && wall2 == 1)
			{
				t.tex = &AssetLoader::sprites[AssetLoader::TRIC];
			}
			else if (xVoid == -1 && (wall1 == 1 && wall2 == 3 || wall1 == 3 && wall2 == 1))
			{
				t.tex = &AssetLoader::sprites[AssetLoader::R];
			}
			else if (xVoid == 1 && (wall1 == 1 && wall2 == 3 || wall1 == 3 && wall2 == 1))
			{
				t.tex = &AssetLoader::sprites[AssetLoader::L];
			}
			else if (wall1 == 1 && wall2 == 4 || wall1 == 4 && wall2 == 1)
			{
				t.tex = &AssetLoader::sprites[AssetLoader::TLIC];
			}

			else if (wall1 == 2 && wall2 == 3 || wall1 == 3 && wall2 == 2)
			{
				t.tex = &AssetLoader::sprites[AssetLoader::BRIC];
			}
			else if (yVoid == -1 && (wall1 == 2 && wall2 == 4 || wall1 == 4 && wall2 == 2))
			{
				t.tex = &AssetLoader::sprites[AssetLoader::D];
			}
			else if (yVoid == 1 && (wall1 == 2 && wall2 == 4 || wall1 == 4 && wall2 == 2))
			{
				t.tex = &AssetLoader::sprites[AssetLoader::T];
			}
			else if (wall1 == 3 && wall2 == 4 || wall1 == 4 && wall2 == 3)
			{
				t.tex = &AssetLoader::sprites[AssetLoader::BLIC];
			}
			else if ((xVoid == -1 && (wall1 == 1 && wall2 == 0 || wall1 == 0 && wall2 == 1)) ||
				(yVoid == -1 && (wall1 == 4 && wall2 == 0 || wall1 == 0 && wall2 == 4)) ||
				(yVoid == -1 && xVoid == -1 && wall1 == 0 && wall2 == 0))
			{
				t.tex = &AssetLoader::sprites[AssetLoader::BROC];
			}
			else if ((xVoid == 1 && (wall1 == 1 && wall2 == 0 || wall1 == 0 && wall2 == 1)) ||
				(yVoid == -1 && (wall1 == 2 && wall2 == 0 || wall1 == 0 && wall2 == 2)) ||
				(yVoid == -1 && xVoid == 1 && wall1 == 0 && wall2 == 0))
			{
				t.tex = &AssetLoader::sprites[AssetLoader::BLOC];
			}
			else if (yVoid == 1 && (wall1 == 2 && wall2 == 0 || wall1 == 0 && wall2 == 2) ||
				(xVoid == 1 && (wall1 == 3 && wall2 == 0 || wall1 == 0 && wall2 == 3)) ||
				(yVoid == 1 && xVoid == 1 && wall1 == 0 && wall2 == 0))
			{
				t.tex = &AssetLoader::sprites[AssetLoader::TLOC];
			}
			else if (xVoid == -1 && (wall1 == 3 && wall2 == 0 || wall1 == 0 && wall2 == 3) ||
				(yVoid == 1 && (wall1 == 4 && wall2 == 0 || wall1 == 0 && wall2 == 4)) ||
				(yVoid == 1 && xVoid == -1 && wall1 == 0 && wall2 == 0))
			{
				t.tex = &AssetLoader::sprites[AssetLoader::TROC];
			}

			//set sprite
			auto s = make_shared<sf::Sprite>(*t.tex);
			s->setPosition(t.pos);
			s->setScale(Vector2f(_tileSize / 200, _tileSize / 200));
			_sprites.push_back(move(s));
		}
		//if thin platform
		else if (getTileAt({ t.pos.x, t.pos.y }) == THIN)
		{
			Vector2ul current(Vector2ul((t.pos - _offset) / (_tileSize)));
			int counter = 0;
			bool left = true;
			//find how many platforms are touching it
			if (current.x != 0 && 
				(getTile({ current.x - 1, current.y }) == THIN) ||
				(getTile({ current.x - 1, current.y }) == TWO_THIN))
			{
				counter++;
			}
			if (current.x != _width - 1 && 
				(getTile({ current.x + 1, current.y }) == THIN) ||
				(getTile({ current.x + 1, current.y }) == TWO_THIN))
			{
				counter++;
				left = false;
			}

			//use correct sprite depeending on the amount of attached walls
			switch (counter)
			{
			case 0:
				t.tex = &AssetLoader::sprites[AssetLoader::SINGLE_P_LONG];
				t.tex->setScale(Vector2f(_tileSize / 100, _tileSize / 100));
				break;
			case 1:
				if (left)
				{
					t.tex = &AssetLoader::sprites[AssetLoader::SINGLE_P_RIGHT];
					t.tex->setScale(Vector2f(_tileSize / 10, _tileSize / 100));
				}
				else
				{
					t.tex = &AssetLoader::sprites[AssetLoader::SINGLE_P_LEFT];
					t.tex->setScale(Vector2f(_tileSize / 10, _tileSize / 100));
				}
				break;
			case 2:
				t.tex = &AssetLoader::sprites[AssetLoader::SINGLE_P_MIDDLE];
				t.tex->setScale(Vector2f(_tileSize / 10, _tileSize / 100));
				break;
			default:
				break;
			}
			//add sprite
			auto s = make_shared<sf::Sprite>(*t.tex);
			s->setPosition(t.pos);
			_sprites.push_back(move(s));
		}
		//if there are 2 thin platforms
		else if (getTileAt({ t.pos.x, t.pos.y }) == TWO_THIN)
		{
			Vector2ul current(Vector2ul((t.pos - _offset) / (_tileSize)));

			//do twice
			for (int i = 0; i < 2; ++i)
			{
				int counter = 0;
				bool left = true;
				//check how many platforms are attached
				if (current.x != 0 && (
					(i == 0 && getTile({ current.x - 1, current.y }) == THIN) ||
					(getTile({ current.x - 1, current.y }) == TWO_THIN) ||
					(i == 1 && getTile({ current.x - 1, current.y }) == LOW_THIN)
					))
				{
					counter++;
				}
				if (current.x != _width - 1 && (
					(i == 0 && getTile({ current.x + 1, current.y }) == THIN) ||
					(getTile({ current.x + 1, current.y }) == TWO_THIN) ||
					(i == 1 && getTile({ current.x + 1, current.y }) == LOW_THIN)
					))
				{
					counter++;
					left = false;
				}
				//choose correct asset
				switch (counter)
				{
				case 0:
					t.tex = &AssetLoader::sprites[AssetLoader::SINGLE_P_LONG];
					t.tex->setScale(Vector2f(_tileSize / 100, _tileSize / 100));
					break;
				case 1:
					if (left)
					{
						t.tex = &AssetLoader::sprites[AssetLoader::SINGLE_P_RIGHT];
						t.tex->setScale(Vector2f(_tileSize / 10, _tileSize / 100));
					}
					else
					{
						t.tex = &AssetLoader::sprites[AssetLoader::SINGLE_P_LEFT];
						t.tex->setScale(Vector2f(_tileSize / 10, _tileSize / 100));
					}
					break;
				case 2:
					t.tex = &AssetLoader::sprites[AssetLoader::SINGLE_P_MIDDLE];
					t.tex->setScale(Vector2f(_tileSize / 10, _tileSize / 100));
					break;
				default:
					break;
				}
				//add sprite
				auto s = make_shared<sf::Sprite>(*t.tex);
				if (i == 0)
					s->setPosition(t.pos);
				else
					s->setPosition(t.pos + Vector2f(0, _tileSize / 2));
				_sprites.push_back(move(s));
			}
		}
		//if there is a low thin platform
		else if (getTileAt({ t.pos.x, t.pos.y }) == LOW_THIN)
		{
			Vector2ul current(Vector2ul((t.pos - _offset) / (_tileSize)));
			int counter = 0;
			bool left = true;
			//check how many walls are attached
			if (current.x != 0 &&
				(getTile({ current.x - 1, current.y }) == LOW_THIN) ||
				(getTile({ current.x - 1, current.y }) == TWO_THIN))
			{
				counter++;
			}
			if (current.x != _width - 1 &&
				(getTile({ current.x + 1, current.y }) == LOW_THIN) ||
				(getTile({ current.x + 1, current.y }) == TWO_THIN))
			{
				counter++;
				left = false;
			}

			//choose correct asset
			switch (counter)
			{
			case 0:
				t.tex = &AssetLoader::sprites[AssetLoader::SINGLE_P_LONG];
				t.tex->setScale(Vector2f(_tileSize / 100, _tileSize / 100));
				break;
			case 1:
				if (left)
				{
					t.tex = &AssetLoader::sprites[AssetLoader::SINGLE_P_RIGHT];
					t.tex->setScale(Vector2f(_tileSize / 10, _tileSize / 100));
				}
				else
				{
					t.tex = &AssetLoader::sprites[AssetLoader::SINGLE_P_LEFT];
					t.tex->setScale(Vector2f(_tileSize / 10, _tileSize / 100));
				}
				break;
			case 2:
				t.tex = &AssetLoader::sprites[AssetLoader::SINGLE_P_MIDDLE];
				t.tex->setScale(Vector2f(_tileSize / 10, _tileSize / 100));
				break;
			default:
				break;
			}
			//add sprite
			auto s = make_shared<sf::Sprite>(*t.tex);
			s->setPosition(t.pos + Vector2f(0, _tileSize/2));
			_sprites.push_back(move(s));
		}
		//if there is a thick platform
		else if (getTileAt({ t.pos.x, t.pos.y }) == THICK)
		{
			Vector2ul current(Vector2ul((t.pos - _offset) / (_tileSize)));
			int counter = 0;
			bool left = true;
			//chack how many thick platforms are attached
			if (current.x != 0 && getTile({ current.x - 1, current.y }) == THICK)
			{
				counter++;
			}
			if (current.x != _width - 1 && getTile({ current.x + 1, current.y }) == THICK)
			{
				counter++;
				left = false;
			}
			//use apppropriate asset
			switch (counter)
			{
			case 0:
				t.tex = &AssetLoader::sprites[AssetLoader::DOUBLE_P_LONG];
				t.tex->setScale(Vector2f(_tileSize / 100, _tileSize / 100));
				break;
			case 1:
				if (left)
				{
					t.tex = &AssetLoader::sprites[AssetLoader::DOUBLE_P_RIGHT];
					t.tex->setScale(Vector2f(_tileSize / 20, _tileSize / 100));
				}
				else
				{
					t.tex = &AssetLoader::sprites[AssetLoader::DOUBLE_P_lEFT];
					t.tex->setScale(Vector2f(_tileSize / 20, _tileSize / 100));
				}
				break;
			case 2:
				t.tex = &AssetLoader::sprites[AssetLoader::DOUBLE_P_MIDDLE];
				t.tex->setScale(Vector2f(_tileSize / 10, _tileSize / 100));
				break;
			default:
				break;
			}
			//add sprite
			auto s = make_shared<sf::Sprite>(*t.tex);
			s->setPosition(t.pos);
			_sprites.push_back(move(s));
		}
		// if there is a low thick platform
		else if (getTileAt({ t.pos.x, t.pos.y }) == LOW_THICK)
		{
			Vector2ul current(Vector2ul((t.pos - _offset) / (_tileSize)));
			int counter = 0;
			bool left = true;
			//find out how many walls are attached
			if (current.x != 0 && getTile({ current.x - 1, current.y }) == LOW_THICK)
			{
				counter++;
			}
			if (current.x != _width - 1 && getTile({ current.x + 1, current.y }) == LOW_THICK)
			{
				counter++;
				left = false;
			}
			//use appropriate asset
			switch (counter)
			{
			case 0:
				t.tex = &AssetLoader::sprites[AssetLoader::DOUBLE_P_LONG];
				t.tex->setScale(Vector2f(_tileSize / 100, _tileSize / 100));
				break;
			case 1:
				if (left)
				{
					t.tex = &AssetLoader::sprites[AssetLoader::DOUBLE_P_RIGHT];
					t.tex->setScale(Vector2f(_tileSize / 20, _tileSize / 100));
				}
				else
				{
					t.tex = &AssetLoader::sprites[AssetLoader::DOUBLE_P_lEFT];
					t.tex->setScale(Vector2f(_tileSize / 20, _tileSize / 100));
				}
				break;
			case 2:
				t.tex = &AssetLoader::sprites[AssetLoader::DOUBLE_P_MIDDLE];
				t.tex->setScale(Vector2f(_tileSize / 10, _tileSize / 100));
				break;
			default:
				break;
			}
			//add sprite
			auto s = make_shared<sf::Sprite>(*t.tex);
			s->setPosition(t.pos + Vector2f(0, _tileSize/2));
			_sprites.push_back(move(s));
		}
		//if tile is inner wall
		else if (getTileAt({ t.pos.x, t.pos.y }) == FILL)
		{
			//set sprite
			t.tex = &AssetLoader::sprites[AssetLoader::TLOC];
			auto s = make_shared<sf::Sprite>(*t.tex);
			s->setScale(Vector2f(_tileSize / 200, _tileSize / 200));
			s->setPosition(t.pos);
			_sprites.push_back(move(s));
		}
	}
}

void LevelSystem::render() {
	for (auto& t : _sprites) {
		Renderer::Queue(&(*t));
	}
}

LevelSystem::Tile LevelSystem::getTile(sf::Vector2ul p) {
	if (p.x > _width || p.y > _height) {
		throw string("Tile out of range: ") + to_string(p.x) + "," +
			to_string(p.y) + ")";
	}
	return _tiles[(p.y * _width) + p.x];
}

size_t LevelSystem::getWidth() { return _width; }

size_t LevelSystem::getHeight() { return _height; }

sf::Vector2f LevelSystem::getTilePosition(sf::Vector2ul p) {
	return (Vector2f(p.x, p.y) * _tileSize) + _offset;
}

std::vector<sf::Vector2ul> LevelSystem::findTiles(LevelSystem::Tile type) {
	auto v = vector<sf::Vector2ul>();
	for (size_t i = 0; i < _width * _height; ++i) {
		if (_tiles[i] == type) {
			v.push_back({ i % _width, i / _width });
		}
	}

	return v;
}

vector<Vector2f> LevelSystem::findTilesV2f(LevelSystem::Tile type) {
	vector<Vector2f> out = vector<Vector2f>();
	for (Vector2ul vec : findTiles(type)) {
		out.push_back(Vector2f(vec) * _tileSize + _offset);
	}
	return out;
}

LevelSystem::Tile LevelSystem::getTileAt(Vector2f v) {
	auto a = v - _offset;
	if (a.x < 0 || a.y < 0) {
		throw string("Tile out of range ");
	}
	return getTile(Vector2ul((v - _offset) / (_tileSize)));
}

bool LevelSystem::isOnGrid(sf::Vector2f v) {
	auto a = v - _offset;
	if (a.x < 0 || a.y < 0) {
		return false;
	}
	auto p = Vector2ul(a / (_tileSize));
	if (p.x > _width || p.y > _height) {
		return false;
	}
	return true;
}

void LevelSystem::setOffset(const Vector2f& _offset) {
	LevelSystem::_offset = _offset;
	buildTextureSprites();
}

void LevelSystem::unload() {
	cout << "LevelSystem unloading\n";
	_sprites.clear();
	_tiles.reset();
	_width = 0;
	_height = 0;
	_offset = { 0, 0 };
}

const Vector2f& LevelSystem::getOffset() { return _offset; }

float LevelSystem::getTileSize() { return _tileSize; }

void LevelSystem::ReSize()
{
	float tileSize = Renderer::GetWindow().getSize().x / _width;
	float off = Renderer::GetWindow().getSize().y - (ls::getHeight() * tileSize);
	for (shared_ptr<Sprite> s : _sprites)
	{
		Vector2f pos = s->getPosition();
		pos -= _offset;
		Vector2ul spos(pos / _tileSize);
		pos = (Vector2f)spos * tileSize;
		pos += {0, off};
		s->setScale(tileSize / 200, tileSize / 200);
		s->setPosition(pos);
	}
	setOffset(Vector2f(0, off));
	// Hacky fix for not resizing to current res.
	if (_tileSize != tileSize) {
		_tileSize = tileSize;
		ReSize();
	}
}