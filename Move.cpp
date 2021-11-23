struct Move {
	int from;
	int to;
	int figure;

	public:
		Move(int from, int to, int figure)
		{
			this->from = from;
			this->to = to;
			this->figure = figure;
		}
};