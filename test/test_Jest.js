// テスト対象の関数群
function sum(a, b) {
  return a + b;
}

function divide(a, b) {
  if (b === 0) throw new Error('Division by zero');
  return a / b;
}

function asyncFetchData() {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve('fetched data');
    }, 100);
  });
}

// Jestのテスト群
describe('基本的な関数のテスト', () => {
  test('sum: 1 + 2 = 3', () => {
    expect(sum(1, 2)).toBe(3);
  });

  test('sum: -1 + -1 = -2', () => {
    expect(sum(-1, -1)).toBe(-2);
  });

  test('divide: 10 / 2 = 5', () => {
    expect(divide(10, 2)).toBe(5);
  });

  test('divide: 0で割ると例外が出る', () => {
    expect(() => divide(10, 0)).toThrow('Division by zero');
  });
});

describe('失敗するテストの例', () => {
  test('sum: 1 + 1 = 3（失敗する）', () => {
    expect(sum(1, 1)).toBe(3); // わざと失敗
  });
});

describe('非同期処理のテスト', () => {
  test('asyncFetchData returns "fetched data"', async () => {
    const data = await asyncFetchData();
    expect(data).toBe('fetched data');
  });
});

describe('マッチャーの例', () => {
  test('toBe vs toEqual', () => {
    const obj1 = { a: 1, b: 2 };
    const obj2 = { a: 1, b: 2 };
    expect(obj1).toEqual(obj2); // オブジェクトの内容が同じか
    expect(obj1).not.toBe(obj2); // 同じオブジェクト参照ではない
  });
});

describe('スナップショットテストの例', () => {
  test('オブジェクトのスナップショット', () => {
    const user = { name: 'Alice', age: 30 };
    expect(user).toMatchSnapshot();
  });
});