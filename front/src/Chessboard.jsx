// eslint-disable-next-line react/prop-types
const Chessboard = ({ boardState = [] }) => {
  // Suponha que boardState seja uma matriz representando o estado atual do tabuleiro

  // Função para renderizar as casas do tabuleiro
  const renderBoard = () => {
    return boardState.map((row, rowIndex) => (
      <div key={rowIndex} className="chessboard-row">
        {row.map((cell, cellIndex) => (
          <div
            key={cellIndex}
            className={`chessboard-cell ${cell === "W" ? "white" : "black"}`}
          >
            {cell}
          </div>
        ))}
      </div>
    ));
  };

  return <div className="chessboard">{renderBoard()}</div>;
};

export default Chessboard;
