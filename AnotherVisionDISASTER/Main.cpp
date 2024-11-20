# include <Siv3D.hpp>

enum class State
{
	Title,
	lab,
	volcano,
	tree,
	driftwood,
	star
};

struct GameData
{
	// ズームできるかフラグ
	int flag = 0;

	// ズーム段階フラグ
	int zoomf = 0;

	const Texture texture_main_1{ Resource(U"images/main_1.png") };

	const Texture texture_main_2{ Resource(U"images/main_2.png") };

	const Texture texture_main_3{ Resource(U"images/main_3.png") };

	const Texture texture_main_4{ Resource(U"images/main_4.png") };

	const Texture texture_main_5{ Resource(U"images/main_5.png") };

	const Texture texture_main_6{ Resource(U"images/main_6.png") };
	
	const Texture texture_main_7{ Resource(U"images/main_7.png") };

	const Texture texture_main_8{ Resource(U"images/main_8.png") };

	const Texture texture_main_9{ Resource(U"images/main_9.png") };

	const Texture texture_main_10{ Resource(U"images/main_10.png") };

	const Texture texture_main_11{ Resource(U"images/main_11.png") };

	const Texture texture_lab_1{ Resource(U"images/lab_1.png") };

	const Texture texture_lab_2{ Resource(U"images/lab_2.png") };

	const Texture texture_lab_3{ Resource(U"images/lab_3.png") };

	const Texture texture_lab_4{ Resource(U"images/lab_4.png") };

	const Texture texture_lab_5{ Resource(U"images/lab_5.png") };

	const Texture texture_lab_6{ Resource(U"images/lab_6.png") };

	const Texture texture_lab_7{ Resource(U"images/lab_7.png") };

	const Texture texture_lab_8{ Resource(U"images/lab_8.png") };

	const Texture texture_lab_9{ Resource(U"images/lab_9.png") };

	const Texture texture_volcano_1{ Resource(U"images/volcano_1.png") };

	const Texture texture_volcano_2{ Resource(U"images/volcano_2.png") };

	const Texture texture_volcano_3{ Resource(U"images/volcano_3.png") };

	const Texture texture_tree_1{ Resource(U"images/tree_1.png") };

	const Texture texture_tree_2{ Resource(U"images/tree_2.png") };

	const Texture texture_tree_3{ Resource(U"images/tree_3.png") };

	const Texture texture_ng{ Resource(U"images/ng.png") };

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
		m_starTransition.update(m_starButton.mouseOver());
		m_staffTransition.update(m_staffButton.mouseOver());

		if (m_labButton.mouseOver() || m_volcanoButton.mouseOver() || m_driftwoodButton.mouseOver() || m_treeButton.mouseOver() || m_starButton.mouseOver() || m_staffButton.mouseOver())
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
		else if (m_starButton.leftClicked())
		{

			changeScene(State::star);
		}
		else if (m_staffTransition.value() == 1 && m_staffButton.leftClicked()) 
		{
			getData().flag ^= 1;
		}
	}

	void draw() const override
	{
		getData().texture_main_1.draw();

		FontAsset(U"TitleFont")(U"望遠鏡")
			.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), 100, Vec2{ 400, 100 });

		m_labButton.draw(ColorF{ 1.0, (1.2 + m_labTransition.value()) / 2.2 }).drawFrame(2);
		m_volcanoButton.draw(ColorF{ 1.0, (1.2 + m_volcanoTransition.value()) / 2.2 }).drawFrame(2);
		m_driftwoodButton.draw(ColorF{ 1.0, (1.2 + m_driftwoodTransition.value()) / 2.2 }).drawFrame(2);
		m_treeButton.draw(ColorF{ 1.0, (1.2 + m_treeTransition.value()) / 2.2 }).drawFrame(2);
		m_starButton.draw(ColorF{ 1.0, (1.2 + m_starTransition.value()) / 2.2 }).drawFrame(2);
		m_staffButton.draw(ColorF{ 0.0, 0.0 });

		FontAsset(U"Menu")(U"研究所").drawAt(m_labButton.center(), ColorF{ 0.25 });
		FontAsset(U"Menu")(U"火山").drawAt(m_volcanoButton.center(), ColorF{ 0.25 });
		FontAsset(U"Menu")(U"流木").drawAt(m_driftwoodButton.center(), ColorF{ 0.25 });
		FontAsset(U"Menu")(U"ヤシの木").drawAt(m_treeButton.center(), ColorF{ 0.25 });
		FontAsset(U"Menu")(U"ヒトデ").drawAt(m_starButton.center(), ColorF{ 0.25 });
	}

private:

	Rect m_labButton{ Arg::center = Scene::Center().movedBy(-300, -150), 350, 100 };
	Transition m_labTransition{ 0.4s, 0.2s };

	Rect m_volcanoButton{ Arg::center = Scene::Center().movedBy(300, -150), 350, 100 };
	Transition m_volcanoTransition{ 0.4s, 0.2s };

	Rect m_driftwoodButton{ Arg::center = Scene::Center().movedBy(-400, 150), 350, 100 };
	Transition m_driftwoodTransition{ 0.4s, 0.2s };

	Rect m_treeButton{ Arg::center = Scene::Center().movedBy(0, 150), 350, 100 };
	Transition m_treeTransition{ 0.4s, 0.2s };

	Rect m_starButton{ Arg::center = Scene::Center().movedBy(400, 150), 350, 100 };
	Transition m_starTransition{ 0.4s, 0.2s };

	Rect m_staffButton{ Arg::center = Scene::Center().movedBy(600, 550), 450, 200 };
	Transition m_staffTransition{ 5.0s, 0.2s };
};

class lab : public App::Scene
{
public:

	lab(const InitData& init)
		: IScene{ init }
	{

	}

	const double tim = Scene::Time();

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

		if (getData().flag == 1 && getData().zoomf < 9 && m_zoominButton.leftClicked())
		{
			getData().zoomf += 1;
		}

		if (getData().flag == 1 && getData().zoomf > 1 && m_zoomoutButton.leftClicked())
		{
			getData().zoomf -= 1;
		}
	}

	void draw() const override
	{	
		if (getData().zoomf == 0)
		{
			const double deltim = Scene::Time() - tim;

			if (deltim < 0.4) getData().texture_main_1.draw();
			else if (deltim < 0.8) getData().texture_main_2.draw();
			else if (deltim < 1.2) getData().texture_main_3.draw();
			else if (deltim < 1.6) getData().texture_main_4.draw();
			else if (deltim < 2.0) getData().texture_main_5.draw();
			else if (deltim < 2.4) getData().texture_main_6.draw();
			else if (deltim < 2.8) getData().texture_main_7.draw();
			else if (deltim < 3.2) getData().texture_main_8.draw();
			else if (deltim < 3.6) getData().texture_main_9.draw();
			else if (deltim < 4.0) getData().texture_main_10.draw();
			else if (deltim < 4.4) getData().texture_main_11.draw();
			else
			{
				getData().zoomf = 1;
			}
		}
		else if (getData().zoomf == 1) getData().texture_lab_1.draw();
		else if (getData().zoomf == 2) getData().texture_lab_2.draw();
		else if (getData().zoomf == 3) getData().texture_lab_3.draw();
		else if (getData().zoomf == 4) getData().texture_lab_4.draw();
		else if (getData().zoomf == 5) getData().texture_lab_5.draw();
		else if (getData().zoomf == 6) getData().texture_lab_6.draw();
		else if (getData().zoomf == 7) getData().texture_lab_7.draw();
		else if (getData().zoomf == 8) getData().texture_lab_8.draw();
		else if (getData().zoomf == 9) getData().texture_lab_9.draw();

		FontAsset(U"TitleFont")(U"研究所")
			.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), 100, Vec2{ 1000, 50 });

		m_exitButton.draw(ColorF{ 1.0, m_exitTransition.value() }).drawFrame(2);
		m_zoominButton.draw(ColorF{ 1.0, m_zoominTransition.value() }).drawFrame(2);
		m_zoomoutButton.draw(ColorF{ 1.0, m_zoomoutTransition.value() }).drawFrame(2);

		FontAsset(U"Menu")(U"戻る").drawAt(m_exitButton.center(), ColorF{ 0.25 });
		FontAsset(U"Menu")(U"拡大する").drawAt(m_zoominButton.center(), ColorF{ 0.25 });
		FontAsset(U"Menu")(U"縮小する").drawAt(m_zoomoutButton.center(), ColorF{ 0.25 });

	}

private:

	Rect m_exitButton{ Arg::center = Scene::Center().movedBy(-650, -440), 400, 80 };
	Transition m_exitTransition{ 0.4s, 0.2s };
	Rect m_zoominButton{ Arg::center = Scene::Center().movedBy(-650, -340), 400, 80 };
	Transition m_zoominTransition{ 0.4s, 0.2s };
	Rect m_zoomoutButton{ Arg::center = Scene::Center().movedBy(-650, -240), 400, 80 };
	Transition m_zoomoutTransition{ 0.4s, 0.2s };

};

class volcano : public App::Scene
{
public:

	volcano(const InitData& init)
		: IScene{ init }
	{

	}

	const double tim = Scene::Time();

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

		if (getData().flag == 1 && getData().zoomf < 3 && m_zoominButton.leftClicked())
		{
			getData().zoomf += 1;
		}

		if (getData().flag == 1 && getData().zoomf > 1 && m_zoomoutButton.leftClicked())
		{
			getData().zoomf -= 1;
		}
	}

	void draw() const override
	{	
		if (getData().zoomf == 0)
		{
			const double deltim = Scene::Time() - tim;

			if (deltim < 0.4) getData().texture_main_1.draw();
			else if (deltim < 0.8) getData().texture_main_2.draw();
			else if (deltim < 1.2) getData().texture_main_3.draw();
			else if (deltim < 1.6) getData().texture_main_4.draw();
			else if (deltim < 2.0) getData().texture_main_5.draw();
			else if (deltim < 2.4) getData().texture_main_6.draw();
			else if (deltim < 2.8) getData().texture_main_7.draw();
			else if (deltim < 3.2) getData().texture_main_8.draw();
			else if (deltim < 3.6) getData().texture_main_9.draw();
			else if (deltim < 4.0) getData().texture_main_10.draw();
			else if (deltim < 4.4) getData().texture_main_11.draw();
			else
			{
				getData().zoomf = 1;
			}
		}
		else if (getData().zoomf == 1) getData().texture_volcano_1.draw();
		else if (getData().zoomf == 2) getData().texture_volcano_2.draw();
		else if (getData().zoomf == 3) getData().texture_volcano_3.draw();

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

	Rect m_exitButton{ Arg::center = Scene::Center().movedBy(-650, -440), 400, 80 };
	Transition m_exitTransition{ 0.4s, 0.2s };
	Rect m_zoominButton{ Arg::center = Scene::Center().movedBy(-650, -340), 400, 80 };
	Transition m_zoominTransition{ 0.4s, 0.2s };
	Rect m_zoomoutButton{ Arg::center = Scene::Center().movedBy(-650, -240), 400, 80 };
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
	}

	void draw() const override
	{
		getData().texture_ng.draw();

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

	Rect m_exitButton{ Arg::center = Scene::Center().movedBy(-650, -440), 400, 80 };
	Transition m_exitTransition{ 0.4s, 0.2s };
	Rect m_zoominButton{ Arg::center = Scene::Center().movedBy(-650, -340), 400, 80 };
	Transition m_zoominTransition{ 0.4s, 0.2s };
	Rect m_zoomoutButton{ Arg::center = Scene::Center().movedBy(-650, -240), 400, 80 };
	Transition m_zoomoutTransition{ 0.4s, 0.2s };

};

class tree : public App::Scene
{
public:

	tree(const InitData& init)
		: IScene{ init }
	{

	}

	const double tim = Scene::Time();

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
		if (getData().flag == 1 && getData().zoomf < 3 && m_zoominButton.leftClicked())
		{
			getData().zoomf += 1;
		}

		if (getData().flag == 1 && getData().zoomf > 1 && m_zoomoutButton.leftClicked())
		{
			getData().zoomf -= 1;
		}
	}

	void draw() const override
	{	
		if (getData().zoomf == 0)
		{
			const double deltim = Scene::Time() - tim;

			if (deltim < 0.4) getData().texture_main_1.draw();
			else if (deltim < 0.8) getData().texture_main_2.draw();
			else if (deltim < 1.2) getData().texture_main_3.draw();
			else if (deltim < 1.6) getData().texture_main_4.draw();
			else if (deltim < 2.0) getData().texture_main_5.draw();
			else if (deltim < 2.4) getData().texture_main_6.draw();
			else if (deltim < 2.8) getData().texture_main_7.draw();
			else if (deltim < 3.2) getData().texture_main_8.draw();
			else if (deltim < 3.6) getData().texture_main_9.draw();
			else if (deltim < 4.0) getData().texture_main_10.draw();
			else if (deltim < 4.4) getData().texture_main_11.draw();
			else
			{
				getData().zoomf = 1;
			}
		}
		else if (getData().zoomf == 1) getData().texture_tree_1.draw();
		else if (getData().zoomf == 2) getData().texture_tree_2.draw();
		else if (getData().zoomf == 3) getData().texture_tree_3.draw();

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

	Rect m_exitButton{ Arg::center = Scene::Center().movedBy(-650, -440), 400, 80 };
	Transition m_exitTransition{ 0.4s, 0.2s };
	Rect m_zoominButton{ Arg::center = Scene::Center().movedBy(-650, -340), 400, 80 };
	Transition m_zoominTransition{ 0.4s, 0.2s };
	Rect m_zoomoutButton{ Arg::center = Scene::Center().movedBy(-650, -240), 400, 80 };
	Transition m_zoomoutTransition{ 0.4s, 0.2s };

};

class star : public App::Scene
{
public:

	star(const InitData& init)
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
	}

	void draw() const override
	{
		getData().texture_ng.draw();

		FontAsset(U"TitleFont")(U"ヒトデ")
			.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), 100, Vec2{ 1000, 50 });

		m_exitButton.draw(ColorF{ 1.0, m_exitTransition.value() }).drawFrame(2);
		m_zoominButton.draw(ColorF{ 1.0, m_zoominTransition.value() }).drawFrame(2);
		m_zoomoutButton.draw(ColorF{ 1.0, m_zoomoutTransition.value() }).drawFrame(2);

		FontAsset(U"Menu")(U"戻る").drawAt(m_exitButton.center(), ColorF{ 0.25 });
		FontAsset(U"Menu")(U"拡大する").drawAt(m_zoominButton.center(), ColorF{ 0.25 });
		FontAsset(U"Menu")(U"縮小する").drawAt(m_zoomoutButton.center(), ColorF{ 0.25 });

	}

private:

	Rect m_exitButton{ Arg::center = Scene::Center().movedBy(-650, -440), 400, 80 };
	Transition m_exitTransition{ 0.4s, 0.2s };
	Rect m_zoominButton{ Arg::center = Scene::Center().movedBy(-650, -340), 400, 80 };
	Transition m_zoominTransition{ 0.4s, 0.2s };
	Rect m_zoomoutButton{ Arg::center = Scene::Center().movedBy(-650, -240), 400, 80 };
	Transition m_zoomoutTransition{ 0.4s, 0.2s };

};

void Main()
{
	Window::Resize(1920, 1080);

	Window::SetStyle(WindowStyle::Frameless);

	Window::SetTitle(U"望遠鏡");

	const Font font{ 25, Typeface::Bold };
	FontAsset::Register(U"TitleFont", FontMethod::MSDF, 50, Typeface::Heavy);
	FontAsset(U"TitleFont").setBufferThickness(4);
	FontAsset::Register(U"Menu", FontMethod::MSDF, 40, Typeface::Medium);

	App manager;
	manager.add<Title>(State::Title);
	manager.add<lab>(State::lab);
	manager.add<volcano>(State::volcano);
	manager.add<driftwood>(State::driftwood);
	manager.add<tree>(State::tree);
	manager.add<star>(State::star);



	while (System::Update())
	{
		if (not manager.update())
		{
			break;
		}
	}
}
