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

class NotificationAddon : public IAddon
{
public:

	/// @brief 通知の種類
	enum class Type
	{
		/// @brief 通常
		Normal,

		/// @brief 情報
		Information,

		/// @brief 疑問
		Question,

		/// @brief 成功
		Success,

		/// @brief 警告
		Warning,

		/// @brief 失敗
		Failure,
	};

	/// @brief 通知のスタイル
	struct Style
	{
		/// @brief 通知の幅
		double width = 300.0;

		/// @brief 通知の背景色
		ColorF backgroundColor{ 0.0, 0.8 };

		/// @brief 通知の枠線色
		ColorF frameColor{ 0.75 };

		/// @brief 通知の文字色
		ColorF textColor{ 1.0 };

		/// @brief 情報アイコンの色
		ColorF informationColor{ 0.0, 0.72, 0.83 };

		/// @brief 疑問アイコンの色
		ColorF questionColor{ 0.39, 0.87, 0.09 };

		/// @brief 成功アイコンの色
		ColorF successColor{ 0.0, 0.78, 0.33 };

		/// @brief 警告アイコンの色
		ColorF warningColor{ 1.0, 0.57, 0.0 };

		/// @brief 失敗アイコンの色
		ColorF failureColor{ 1.00, 0.32, 0.32 };
	};

	/// @brief 通知を表示します。
	/// @param message メッセージ
	/// @param type 通知の種類
	static void Show(const StringView message, const Type type = NotificationAddon::Type::Normal)
	{
		if (auto p = Addon::GetAddon<NotificationAddon>(U"NotificationAddon"))
		{
			p->show(message, type);
		}
	}

	/// @brief 通知の表示時間を設定します。
	/// @param lifeTime 表示時間（秒）
	static void SetLifeTime(const double lifeTime)
	{
		if (auto p = Addon::GetAddon<NotificationAddon>(U"NotificationAddon"))
		{
			p->m_lifeTime = lifeTime;
		}
	}

	/// @brief 通知のスタイルを設定します。
	/// @param style スタイル
	static void SetStyle(const Style& style)
	{
		if (auto p = Addon::GetAddon<NotificationAddon>(U"NotificationAddon"))
		{
			p->m_style = style;
		}
	}

private:

	static constexpr StringView Icons = U" \U000F02FC\U000F02D7\U000F0E1E\U000F0029\U000F1398";

	struct Notification
	{
		String message;

		double time = 0.0;

		double currentIndex = 0.0;

		double velocity = 0.0;

		Type type = Type::Normal;
	};

	Style m_style;

	Array<Notification> m_notifications;

	double m_lifeTime = 10.0;

	bool update() override
	{
		const double deltaTime = Scene::DeltaTime();

		for (auto& notification : m_notifications)
		{
			notification.time += deltaTime;
		}

		m_notifications.remove_if([lifeTime = m_lifeTime](const Notification& notification) { return (lifeTime < notification.time); });

		for (size_t i = 0; i < m_notifications.size(); ++i)
		{
			auto& notification = m_notifications[i];
			notification.currentIndex = Math::SmoothDamp(notification.currentIndex, static_cast<double>(i), notification.velocity, 0.15, 9999.0, deltaTime);
		}

		return true;
	}

	void draw() const override
	{
		const Font& font = SimpleGUI::GetFont();

		for (const auto& notification : m_notifications)
		{
			double xScale = 1.0;
			double alpha = 1.0;

			if (notification.time < 0.2)
			{
				xScale = alpha = (notification.time / 0.2);
			}
			else if ((m_lifeTime - 0.4) < notification.time)
			{
				alpha = ((m_lifeTime - notification.time) / 0.4);
			}

			alpha = EaseOutExpo(alpha);
			xScale = EaseOutExpo(xScale);

			ColorF backgroundColor = m_style.backgroundColor;
			backgroundColor.a *= alpha;

			ColorF frameColor = m_style.frameColor;
			frameColor.a *= alpha;

			ColorF textColor = m_style.textColor;
			textColor.a *= alpha;

			const RectF rect{ 10, (10 + notification.currentIndex * 32), (m_style.width * xScale), 31 };
			rect.rounded(3).draw(backgroundColor).drawFrame(1, 0, frameColor);

			if (notification.type != Type::Normal)
			{
				ColorF color = notification.type == Type::Information ? m_style.informationColor
					: notification.type == Type::Question ? m_style.questionColor
					: notification.type == Type::Success ? m_style.successColor
					: notification.type == Type::Warning ? m_style.warningColor
					: m_style.failureColor;
				color.a *= alpha;

				font(Icons[FromEnum(notification.type)]).draw(18, Arg::leftCenter = rect.leftCenter().movedBy(8, -1), color);
			}

			font(notification.message).draw(18, Arg::leftCenter = rect.leftCenter().movedBy(32, -1), textColor);
		}
	}

	void show(const StringView message, const Type type)
	{
		const double currentIndex = (m_notifications.empty() ? 0.0 : m_notifications.back().currentIndex + 1.0);
		const double velocity = (m_notifications.empty() ? 0.0 : m_notifications.back().velocity);

		m_notifications << Notification{
			.message = String{ message },
			.time = 0.0,
			.currentIndex = currentIndex,
			.velocity = velocity,
			.type = type };
	}
};


struct GameData
{
	// ズームできるかフラグ
	int flag = 0;
	int count = 0;

	// ズーム段階フラグ
	int zoomf = 0;

	// ズーム演出フラグ
	int zoom_lab = 1;
	double tim = 0.0;

	const Texture texture_main{ Resource(U"images/main.png") };

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

		if (m_labButton.mouseOver() || m_volcanoButton.mouseOver() || m_driftwoodButton.mouseOver() || m_treeButton.mouseOver() || m_starButton.mouseOver() || m_staffButton.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}

		if (m_labButton.leftClicked())
		{
			NotificationAddon::Show(U"方向を合わせています。", NotificationAddon::Type::Information);
			getData().tim = Scene::Time();
			changeScene(State::lab);
			NotificationAddon::Show(U"拡大率を合わせています。", NotificationAddon::Type::Information);
		}
		else if (m_volcanoButton.leftClicked())
		{
			NotificationAddon::Show(U"方向を合わせています。", NotificationAddon::Type::Information);
			changeScene(State::volcano);
			NotificationAddon::Show(U"拡大率を合わせています。", NotificationAddon::Type::Information);
		}
		else if (m_driftwoodButton.leftClicked())
		{
			NotificationAddon::Show(U"方向を合わせています。", NotificationAddon::Type::Information);
			changeScene(State::driftwood);
			NotificationAddon::Show(U"拡大率を合わせています。", NotificationAddon::Type::Information);
		}
		else if (m_treeButton.leftClicked())
		{
			NotificationAddon::Show(U"方向を合わせています。", NotificationAddon::Type::Information);
			changeScene(State::tree);
			NotificationAddon::Show(U"拡大率を合わせています。", NotificationAddon::Type::Information);
		}
		else if (m_starButton.leftClicked())
		{
			NotificationAddon::Show(U"方向を合わせています。", NotificationAddon::Type::Information);
			changeScene(State::star);
			NotificationAddon::Show(U"拡大率を合わせています。", NotificationAddon::Type::Information);
		}
		else if (m_staffButton.leftClicked())
		{
			if (getData().count < 4) getData().count++;
			else
			{
				getData().zoom_lab = 1;
				getData().flag ^= 1;
				getData().count = 0;

				if(getData().flag) 
				{
					NotificationAddon::Show(U"ズームアウトが有効になりました。", NotificationAddon::Type::Information);
					NotificationAddon::Show(U"演出が初期化されました。", NotificationAddon::Type::Information);
				}
				else
				{
					NotificationAddon::Show(U"ズームアウトが無効になりました。", NotificationAddon::Type::Information);
					NotificationAddon::Show(U"演出が初期化されました。", NotificationAddon::Type::Information);
				}

			}
		}
	}

	void draw() const override
	{
		getData().texture_main.resized(1920, 1080).draw();

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

	RoundRect m_labButton{ Arg::center = Scene::Center().movedBy(-300, -150), 350, 100, 10 };
	Transition m_labTransition{ 0.4s, 0.2s };

	RoundRect m_volcanoButton{ Arg::center = Scene::Center().movedBy(300, -150), 350, 100, 10 };
	Transition m_volcanoTransition{ 0.4s, 0.2s };

	RoundRect m_driftwoodButton{ Arg::center = Scene::Center().movedBy(-400, 150), 350, 100, 10 };
	Transition m_driftwoodTransition{ 0.4s, 0.2s };

	RoundRect m_treeButton{ Arg::center = Scene::Center().movedBy(0, 150), 350, 100, 10 };
	Transition m_treeTransition{ 0.4s, 0.2s };

	RoundRect m_starButton{ Arg::center = Scene::Center().movedBy(400, 150), 350, 100, 10 };
	Transition m_starTransition{ 0.4s, 0.2s };

	Rect m_staffButton{ Arg::center = Scene::Center().movedBy(600, 550), 450, 200 };
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
		
		if (m_zoominButton.leftClicked())
		{
			if(getData().zoomf < 23) getData().zoomf += 1;
		}

		if (m_zoomoutButton.leftClicked())
		{
			if (getData().zoomf > 0) getData().zoomf -= 1;
			else if (getData().flag == 1 && getData().zoomf > -11) getData().zoomf -= 1;
			else NotificationAddon::Show(U"これ以上ズームアウトできません。", NotificationAddon::Type::Failure);
		}
	}

	void draw() const override
	{	
		/*if (getData().zoomf == 0)
		{	
			
			const double deltim = Scene::Time() - getData().tim;
			if (!getData().zoom_lab)
			{
				getData().zoomf = 1;
			}
			else if (deltim < 0.4) getData().texture_main_1.draw();
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
				getData().zoom_lab = 0;
				getData().zoomf = 1;
			}
		}*/
		if (getData().zoomf == 0) getData().texture_lab_1.draw();
		else if (getData().zoomf == 1) getData().texture_lab_2.draw();
		else if (getData().zoomf == 2) getData().texture_lab_3.draw();
		else if (getData().zoomf == 3) getData().texture_lab_4.draw();
		else if (getData().zoomf == 4) getData().texture_lab_5.draw();
		else if (getData().zoomf == 5) getData().texture_lab_6.draw();
		else if (getData().zoomf == 6) getData().texture_lab_7.draw();
		else if (getData().zoomf == 7) getData().texture_lab_8.draw();
		else if (getData().zoomf > 7) getData().texture_lab_9.scaled(pow(1.1, Min<double>(getData().zoomf - 9, 15))).drawAt(Scene::Center());
		else if (getData().zoomf == -1) getData().texture_main_11.draw();
		else if (getData().zoomf == -2) getData().texture_main_10.draw();
		else if (getData().zoomf == -3) getData().texture_main_9.draw();
		else if (getData().zoomf == -4) getData().texture_main_8.draw();
		else if (getData().zoomf == -5) getData().texture_main_7.draw();
		else if (getData().zoomf == -6) getData().texture_main_6.draw();
		else if (getData().zoomf == -7) getData().texture_main_5.draw();
		else if (getData().zoomf == -8) getData().texture_main_4.draw();
		else if (getData().zoomf == -9) getData().texture_main_3.draw();
		else if (getData().zoomf == -10) getData().texture_main_2.draw();
		else if (getData().zoomf == -11) getData().texture_main_1.draw();


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

	RoundRect m_exitButton{ Arg::center = Scene::Center().movedBy(-650, -380), 400, 80, 10 };
	Transition m_exitTransition{ 0.4s, 0.2s };
	RoundRect m_zoominButton{ Arg::center = Scene::Center().movedBy(-650, -280), 400, 80, 10 };
	Transition m_zoominTransition{ 0.4s, 0.2s };
	RoundRect m_zoomoutButton{ Arg::center = Scene::Center().movedBy(-650, -180), 400, 80, 10 };
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

		if (m_zoominButton.leftClicked())
		{
			if (getData().zoomf < 16) getData().zoomf += 1;
		}

		if (m_zoomoutButton.leftClicked())
		{
			if (getData().zoomf > 0) getData().zoomf -= 1;
			else NotificationAddon::Show(U"これ以上ズームアウトできません。", NotificationAddon::Type::Failure);
		}
	}

	void draw() const override
	{	
		if (getData().zoomf == 0) getData().texture_volcano_1.draw();
		else if (getData().zoomf == 1) getData().texture_volcano_2.draw();
		else if (getData().zoomf > 1) getData().texture_volcano_3.scaled(pow(1.1, Min<double>(getData().zoomf - 2, 15))).drawAt(Scene::Center());

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

	RoundRect m_exitButton{ Arg::center = Scene::Center().movedBy(-650, -380), 400, 80, 10 };
	Transition m_exitTransition{ 0.4s, 0.2s };
	RoundRect m_zoominButton{ Arg::center = Scene::Center().movedBy(-650, -280), 400, 80, 10 };
	Transition m_zoominTransition{ 0.4s, 0.2s };
	RoundRect m_zoomoutButton{ Arg::center = Scene::Center().movedBy(-650, -180), 400, 80, 10 };
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

	RoundRect m_exitButton{ Arg::center = Scene::Center().movedBy(-650, -380), 400, 80, 10 };
	Transition m_exitTransition{ 0.4s, 0.2s };
	RoundRect m_zoominButton{ Arg::center = Scene::Center().movedBy(-650, -280), 400, 80, 10 };
	Transition m_zoominTransition{ 0.4s, 0.2s };
	RoundRect m_zoomoutButton{ Arg::center = Scene::Center().movedBy(-650, -180), 400, 80, 10 };
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

		if (m_zoominButton.leftClicked())
		{
			if (getData().zoomf < 16) getData().zoomf += 1;
		}

		if (m_zoomoutButton.leftClicked())
		{
			if(getData().zoomf > 0) getData().zoomf -= 1;
			else NotificationAddon::Show(U"これ以上ズームアウトできません。", NotificationAddon::Type::Failure);
		}
	}

	void draw() const override
	{	
		if (getData().zoomf == 0) getData().texture_tree_1.draw();
		else if (getData().zoomf == 1) getData().texture_tree_2.draw();
		else if (getData().zoomf > 1) getData().texture_tree_3.scaled(pow(1.1, Min<double>(getData().zoomf - 2, 15))).drawAt(Scene::Center());

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

	RoundRect m_exitButton{ Arg::center = Scene::Center().movedBy(-650, -380), 400, 80, 10 };
	Transition m_exitTransition{ 0.4s, 0.2s };
	RoundRect m_zoominButton{ Arg::center = Scene::Center().movedBy(-650, -280), 400, 80, 10 };
	Transition m_zoominTransition{ 0.4s, 0.2s };
	RoundRect m_zoomoutButton{ Arg::center = Scene::Center().movedBy(-650, -180), 400, 80, 10 };
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

	RoundRect m_exitButton{ Arg::center = Scene::Center().movedBy(-650, -380), 400, 80, 10 };
	Transition m_exitTransition{ 0.4s, 0.2s };
	RoundRect m_zoominButton{ Arg::center = Scene::Center().movedBy(-650, -280), 400, 80, 10 };
	Transition m_zoominTransition{ 0.4s, 0.2s };
	RoundRect m_zoomoutButton{ Arg::center = Scene::Center().movedBy(-650, -180), 400, 80, 10 };
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

	Addon::Register<NotificationAddon>(U"NotificationAddon");

	while (System::Update())
	{
		if (not manager.update())
		{
			break;
		}
	}
}
