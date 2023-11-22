import { BrowserRouter as Router, Route, Routes  } from "react-router-dom";
import Bfs from "./Bfs";
import Dfs from './Dfs';

const App = () => {
  return (
    <Router>
      <Routes>
        <Route exact path="/" Component={Bfs} />
        <Route exact path="/dfs" Component={Dfs} />
      </Routes>
    </Router>
  );
};

export default App;
