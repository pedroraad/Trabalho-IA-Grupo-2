// eslint-disable-next-line react/prop-types
const Chessboard = ({ boardState = [] }) => {
  // Suponha que boardState seja uma matriz representando o estado atual do tabuleiro

  // Função para renderizar as casas do tabuleiro
  const renderBoard = () => {
    const board = arrayToMatrix(boardState, 5, 5);

    return board.map((row, rowIndex) => (
      <div key={rowIndex} className="chessboard-row">
        {row.map((cell, cellIndex) => (
          <div
            key={cellIndex}
            className={`chessboard-cell ${cell === "W" ? "white" : "black"}`}
          >
            {cell == "-1" ? "" : cell}
          </div>
        ))}
      </div>
    ));
  };

  function arrayToMatrix(arr, rows, cols) {
    if (arr.length !== rows * cols) {
      return []
    }

    let matrix = [];
    for (let i = 0; i < rows; i++) {
      matrix.push(arr.slice(i * cols, (i + 1) * cols));
    }

    return matrix;
  }

  return <div className="chessboard">{renderBoard()}</div>;
};

export default Chessboard;
