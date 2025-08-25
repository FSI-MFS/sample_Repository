# テスト対象の関数
def add(a, b):
    return a + b

def subtract(a, b):
    return a - b

# Pytest によるテスト関数
def test_add():
    assert add(2, 3) == 5
    assert add(-1, 1) == 0
    assert add(0, 0) == 0

def test_subtract():
    assert subtract(5, 2) == 3
    assert subtract(0, 1) == -1
    assert subtract(-1, -1) == 0