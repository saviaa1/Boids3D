class Drawing {
public:
	Drawing() {
		positions_ = new float[12] {
			-0.5f, -1.0f, 0.433f,
			0.5f, -1.0f, 0.433f,
			0.0f, 1.0f, 0.0f,
			0.0f, -1.0f, -0.433f
		};

		indices_ = new unsigned int[12] {
			0, 1, 2,
			1, 3, 2,
			3, 0, 2,
			0, 1, 3
		};
	}

	float* GetPositions() const {
		return positions_;
	}

	unsigned int* GetIndices() const {
		return indices_;
	}

private:
	float *positions_;
	unsigned int *indices_;
};