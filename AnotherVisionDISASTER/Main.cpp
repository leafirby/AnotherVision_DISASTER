# include <Siv3D.hpp>

enum class State
{
	Title,
	lab,
	volcano,
	tree,
	driftwood
};

struct GameData
{
	// ズームできるかフラグ
	int flag = 0;

	// ズーム段階フラグ
	int zoomf = 0;

	const Texture texture_main{ Resource(U"images/main.png") };

	const Texture texture_lab_1{ Resource(U"images/lab_1.png") };

	const Texture texture_lab_2{ Resource(U"images/lab_2.png") };

	const Texture texture_volcano_1{ Resource(U"images/volcano_1.png") };

	const Texture texture_volcano_2{ Resource(U"images/volcano_2.png") };

	const Texture texture_driftwood_1{ Resource(U"images/driftwood_1.png") };

	const Texture texture_driftwood_2{ Resource(U"images/driftwood_2.png") };

	const Texture texture_tree_1{ Resource(U"images/tree_1.png") };

	const Texture texture_tree_2{ Resource(U"images/tree_2.png") };

	const Texture texture_exit{ Resource(U"images/exit.png") };

	const Texture texture_zoomin{ Resource(U"images/zoomin.png") };

	const Texture texture_zoomout{ Resource(U"images/zoomout.png") };

};

using App = SceneManager<State, GameData>;

class Title : public App::Scene
{
public:

	Title(const InitData& init)
		: IScene{ init } {}

	void update() override
	{
		m_labTransition.update(m_labButton.mouseOver());
		m_volcanoTransition.update(m_volcanoButton.mouseOver());
		m_driftwoodTransition.update(m_driftwoodButton.mouseOver());
		m_treeTransition.update(m_treeButton.mouseOver());
		m_staffTransition.update(m_staffButton.mouseOver());

		if (m_labButton.mouseOver() || m_volcanoButton.mouseOver() || m_driftwoodButton.mouseOver() || m_treeButton.mouseOver() || m_staffButton.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}

		if (m_labButton.leftClicked())
		{
			changeScene(State::lab);
		}
		else if (m_volcanoButton.leftClicked())
		{
			changeScene(State::volcano);
		}
		else if (m_driftwoodButton.leftClicked())
		{
			changeScene(State::driftwood);
		}
		else if (m_treeButton.leftClicked())
		{
			changeScene(State::tree);
		}
		else if (m_staffButton.leftClicked())
		{
			getData().flag ^= 1;
		}
	}

	void draw() const override
	{
		getData().texture_main.resized(1280).draw();

		FontAsset(U"TitleFont")(U"望遠鏡")
			.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), 100, Vec2{ 400, 100 });

		m_labButton.draw(ColorF{ 1.0, m_labTransition.value() }).drawFrame(2);
		m_volcanoButton.draw(ColorF{ 1.0, m_volcanoTransition.value() }).drawFrame(2);
		m_driftwoodButton.draw(ColorF{ 1.0, m_driftwoodTransition.value() }).drawFrame(2);
		m_treeButton.draw(ColorF{ 1.0, m_treeTransition.value() }).drawFrame(2);
		m_staffButton.draw(ColorF{ 0.0, m_staffTransition.value() }).drawFrame(2);

		FontAsset(U"Menu")(U"研究所").drawAt(m_labButton.center(), ColorF{ 0.25 });
		FontAsset(U"Menu")(U"火山").drawAt(m_volcanoButton.center(), ColorF{ 0.25 });
		FontAsset(U"Menu")(U"流木").drawAt(m_driftwoodButton.center(), ColorF{ 0.25 });
		FontAsset(U"Menu")(U"ヤシの木").drawAt(m_treeButton.center(), ColorF{ 0.25 });
	}

private:

	Rect m_labButton{ Arg::center = Scene::Center().movedBy(-300, -150), 300, 60 };
	Transition m_labTransition{ 0.4s, 0.2s };

	Rect m_volcanoButton{ Arg::center = Scene::Center().movedBy(300, -150), 300, 60 };
	Transition m_volcanoTransition{ 0.4s, 0.2s };

	Rect m_driftwoodButton{ Arg::center = Scene::Center().movedBy(-300, 150), 300, 60 };
	Transition m_driftwoodTransition{ 0.4s, 0.2s };

	Rect m_treeButton{ Arg::center = Scene::Center().movedBy(300, 150), 300, 60 };
	Transition m_treeTransition{ 0.4s, 0.2s };

	Rect m_staffButton{ Arg::center = Scene::Center().movedBy(500, 500), 300, 60 };
	Transition m_staffTransition{ 0.4s, 0.2s };
};

class lab : public App::Scene
{
public:

	lab(const InitData& init)
		: IScene{ init }
	{

	}

	void update() override
	{
		m_exitTransition.update(m_exitButton.mouseOver());
		m_zoominTransition.update(m_zoominButton.mouseOver());
		m_zoomoutTransition.update(m_zoomoutButton.mouseOver());

		if (m_exitButton.mouseOver() || m_zoominButton.mouseOver() || m_zoomoutButton.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}

		if (m_exitButton.leftClicked())
		{
			getData().zoomf = 0;
			changeScene(State::Title);
		}

		if (getData().flag == 1 && getData().zoomf < 2 && m_zoominButton.leftClicked())
		{
			getData().zoomf += 1;
		}

		if (getData().flag == 1 && getData().zoomf > 0 && m_zoomoutButton.leftClicked())
		{
			getData().zoomf -= 1;
		}
	}

	void draw() const override
	{
		if (getData().zoomf == 0) getData().texture_main.resized(1280).draw();
		else if (getData().zoomf == 1) getData().texture_lab_1.resized(1280).draw();
		else if (getData().zoomf == 2) getData().texture_lab_2.resized(1280).draw();

		FontAsset(U"TitleFont")(U"研究所")
			.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), 100, Vec2{ 1000, 50 });

		m_exitButton.draw(ColorF{ 1.0, m_exitTransition.value() }).drawFrame(2);
		m_zoominButton.draw(ColorF{ 1.0, m_zoominTransition.value() }).drawFrame(2);
		m_zoomoutButton.draw(ColorF{ 1.0, m_zoomoutTransition.value() }).drawFrame(2);

		FontAsset(U"Menu")(U"戻る").drawAt(m_exitButton.center(), ColorF{ 0.25 });
		FontAsset(U"Menu")(U"拡大する").drawAt(m_zoominButton.center(), ColorF{ 0.25 });
		FontAsset(U"Menu")(U"縮小する").drawAt(m_zoomoutButton.center(), ColorF{ 0.25 });

		/*
		if (flags == 0) {
			texture_1.resized(1280).draw();

			const RoundRect rr{ 50, 60, 300, 80, 40 };
			rr.drawShadow(Vec2{ 4, 4 }, 20, 0)
				.draw();

			Circle{ rr.rect.pos.movedBy(rr.r, rr.r), rr.r }
				.stretched(-5)
				.draw(HSV{ 40, 0.5, 1.0 });

			font(U"拡大する").draw({ 160, 80, 300, 80 }, ColorF{ 0.25 });

			const RoundRect rr2{ 50, 160, 300, 80, 40 };
			rr2.drawShadow(Vec2{ 4, 4 }, 20, 0)
				.draw(ColorF{ 0.8 });

			Circle{ rr2.rect.pos.movedBy(rr2.r, rr2.r), rr2.r }
				.stretched(-5)
				.draw(HSV{ 40, 0.5, 1.0 });

			font(U"縮小する").draw({ 160, 180, 300, 80 }, ColorF{ 0.25 });

			Circle{ Cursor::Pos(), 40 }.draw(ColorF{ 0.0, 0.5, 1.0, 0.6 });

			if (rr.leftClicked())
			{
				flags = 4;
			}
		}
		*/

	}

private:

	Rect m_exitButton{ Arg::center = Scene::Center().movedBy(-400, -400), 300, 60 };
	Transition m_exitTransition{ 0.4s, 0.2s };
	Rect m_zoominButton{ Arg::center = Scene::Center().movedBy(-400, -300), 300, 60 };
	Transition m_zoominTransition{ 0.4s, 0.2s };
	Rect m_zoomoutButton{ Arg::center = Scene::Center().movedBy(-400, -200), 300, 60 };
	Transition m_zoomoutTransition{ 0.4s, 0.2s };

};

class volcano : public App::Scene
{
public:

	volcano(const InitData& init)
		: IScene{ init }
	{

	}

	void update() override
	{
		m_exitTransition.update(m_exitButton.mouseOver());
		m_zoominTransition.update(m_zoominButton.mouseOver());
		m_zoomoutTransition.update(m_zoomoutButton.mouseOver());

		if (m_exitButton.mouseOver() || m_zoominButton.mouseOver() || m_zoomoutButton.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}

		if (m_exitButton.leftClicked())
		{
			getData().zoomf = 0;
			changeScene(State::Title);
		}

		if (getData().flag == 1 && getData().zoomf < 2 && m_zoominButton.leftClicked())
		{
			getData().zoomf += 1;
		}

		if (getData().flag == 1 && getData().zoomf > 0 && m_zoomoutButton.leftClicked())
		{
			getData().zoomf -= 1;
		}
	}

	void draw() const override
	{
		if (getData().zoomf == 0) getData().texture_main.resized(1280).draw();
		else if (getData().zoomf == 1) getData().texture_volcano_1.resized(1280).draw();
		else if (getData().zoomf == 2) getData().texture_volcano_2.resized(1280).draw();

		FontAsset(U"TitleFont")(U"火山")
			.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), 100, Vec2{ 1000, 50 });

		m_exitButton.draw(ColorF{ 1.0, m_exitTransition.value() }).drawFrame(2);
		m_zoominButton.draw(ColorF{ 1.0, m_zoominTransition.value() }).drawFrame(2);
		m_zoomoutButton.draw(ColorF{ 1.0, m_zoomoutTransition.value() }).drawFrame(2);

		FontAsset(U"Menu")(U"戻る").drawAt(m_exitButton.center(), ColorF{ 0.25 });
		FontAsset(U"Menu")(U"拡大する").drawAt(m_zoominButton.center(), ColorF{ 0.25 });
		FontAsset(U"Menu")(U"縮小する").drawAt(m_zoomoutButton.center(), ColorF{ 0.25 });

	}

private:

	Rect m_exitButton{ Arg::center = Scene::Center().movedBy(-400, -400), 300, 60 };
	Transition m_exitTransition{ 0.4s, 0.2s };
	Rect m_zoominButton{ Arg::center = Scene::Center().movedBy(-400, -300), 300, 60 };
	Transition m_zoominTransition{ 0.4s, 0.2s };
	Rect m_zoomoutButton{ Arg::center = Scene::Center().movedBy(-400, -200), 300, 60 };
	Transition m_zoomoutTransition{ 0.4s, 0.2s };

};

class driftwood : public App::Scene
{
public:

	driftwood(const InitData& init)
		: IScene{ init }
	{

	}

	void update() override
	{
		m_exitTransition.update(m_exitButton.mouseOver());
		m_zoominTransition.update(m_zoominButton.mouseOver());
		m_zoomoutTransition.update(m_zoomoutButton.mouseOver());

		if (m_exitButton.mouseOver() || m_zoominButton.mouseOver() || m_zoomoutButton.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}

		if (m_exitButton.leftClicked())
		{
			getData().zoomf = 0;
			changeScene(State::Title);
		}

		if (getData().flag == 1 && getData().zoomf < 2 && m_zoominButton.leftClicked())
		{
			getData().zoomf += 1;
		}

		if (getData().flag == 1 && getData().zoomf > 0 && m_zoomoutButton.leftClicked())
		{
			getData().zoomf -= 1;
		}
	}

	void draw() const override
	{
		if (getData().zoomf == 0) getData().texture_main.resized(1280).draw();
		else if (getData().zoomf == 1) getData().texture_driftwood_1.resized(1280).draw();
		else if (getData().zoomf == 2) getData().texture_driftwood_2.resized(1280).draw();

		FontAsset(U"TitleFont")(U"流木")
			.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), 100, Vec2{ 1000, 50 });

		m_exitButton.draw(ColorF{ 1.0, m_exitTransition.value() }).drawFrame(2);
		m_zoominButton.draw(ColorF{ 1.0, m_zoominTransition.value() }).drawFrame(2);
		m_zoomoutButton.draw(ColorF{ 1.0, m_zoomoutTransition.value() }).drawFrame(2);

		FontAsset(U"Menu")(U"戻る").drawAt(m_exitButton.center(), ColorF{ 0.25 });
		FontAsset(U"Menu")(U"拡大する").drawAt(m_zoominButton.center(), ColorF{ 0.25 });
		FontAsset(U"Menu")(U"縮小する").drawAt(m_zoomoutButton.center(), ColorF{ 0.25 });

	}

private:

	Rect m_exitButton{ Arg::center = Scene::Center().movedBy(-400, -400), 300, 60 };
	Transition m_exitTransition{ 0.4s, 0.2s };
	Rect m_zoominButton{ Arg::center = Scene::Center().movedBy(-400, -300), 300, 60 };
	Transition m_zoominTransition{ 0.4s, 0.2s };
	Rect m_zoomoutButton{ Arg::center = Scene::Center().movedBy(-400, -200), 300, 60 };
	Transition m_zoomoutTransition{ 0.4s, 0.2s };

};

class tree : public App::Scene
{
public:

	tree(const InitData& init)
		: IScene{ init }
	{

	}

	void update() override
	{
		m_exitTransition.update(m_exitButton.mouseOver());
		m_zoominTransition.update(m_zoominButton.mouseOver());
		m_zoomoutTransition.update(m_zoomoutButton.mouseOver());

		if (m_exitButton.mouseOver() || m_zoominButton.mouseOver() || m_zoomoutButton.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}

		if (m_exitButton.leftClicked())
		{
			getData().zoomf = 0;
			changeScene(State::Title);
		}

		if (getData().flag == 1 && getData().zoomf < 2 && m_zoominButton.leftClicked())
		{
			getData().zoomf += 1;
		}

		if (getData().flag == 1 && getData().zoomf > 0 && m_zoomoutButton.leftClicked())
		{
			getData().zoomf -= 1;
		}
	}

	void draw() const override
	{
		if (getData().zoomf == 0) getData().texture_main.resized(1280).draw();
		else if (getData().zoomf == 1) getData().texture_tree_1.resized(1280).draw();
		else if (getData().zoomf == 2) getData().texture_tree_2.resized(1280).draw();

		FontAsset(U"TitleFont")(U"ヤシの木")
			.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), 100, Vec2{ 1000, 50 });

		m_exitButton.draw(ColorF{ 1.0, m_exitTransition.value() }).drawFrame(2);
		m_zoominButton.draw(ColorF{ 1.0, m_zoominTransition.value() }).drawFrame(2);
		m_zoomoutButton.draw(ColorF{ 1.0, m_zoomoutTransition.value() }).drawFrame(2);

		FontAsset(U"Menu")(U"戻る").drawAt(m_exitButton.center(), ColorF{ 0.25 });
		FontAsset(U"Menu")(U"拡大する").drawAt(m_zoominButton.center(), ColorF{ 0.25 });
		FontAsset(U"Menu")(U"縮小する").drawAt(m_zoomoutButton.center(), ColorF{ 0.25 });

	}

private:

	Rect m_exitButton{ Arg::center = Scene::Center().movedBy(-400, -400), 300, 60 };
	Transition m_exitTransition{ 0.4s, 0.2s };
	Rect m_zoominButton{ Arg::center = Scene::Center().movedBy(-400, -300), 300, 60 };
	Transition m_zoominTransition{ 0.4s, 0.2s };
	Rect m_zoomoutButton{ Arg::center = Scene::Center().movedBy(-400, -200), 300, 60 };
	Transition m_zoomoutTransition{ 0.4s, 0.2s };

};

void Main()
{
	Window::Resize(1280, 960);

	CursorStyle::Hand;

	Window::SetStyle(WindowStyle::Frameless);

	Window::SetTitle(U"望遠鏡");

	const Font font{ 25, Typeface::Bold };
	FontAsset::Register(U"TitleFont", FontMethod::MSDF, 50, U"example/font/RocknRoll/RocknRollOne-Regular.ttf");
	FontAsset(U"TitleFont").setBufferThickness(4);
	FontAsset::Register(U"Menu", FontMethod::MSDF, 40, Typeface::Medium);
	FontAsset::Register(U"Ranking", 40, Typeface::Heavy);
	FontAsset::Register(U"GameScore", 30, Typeface::Light);
	AudioAsset::Register(U"Brick", GMInstrument::Woodblock, PianoKey::C5, 0.2s, 0.1s);

	App manager;
	manager.add<Title>(State::Title);
	manager.add<lab>(State::lab);
	manager.add<volcano>(State::volcano);
	manager.add<driftwood>(State::driftwood);
	manager.add<tree>(State::tree);


	while (System::Update())
	{
		if (not manager.update())
		{
			break;
		}
	}
}
